#include "AbstractConverter.h"
#include "ArrayConverter.h"
#include "ArrayOfArraysConverter.h"
#include "AsyncWorker.h"
#include "Converters.h"
#include "InstanceConverter.h"
#include "IWorker.h"
#include "ObjectWrap.h"
#include "PrimitiveTypeConverters.h"
#include "TryCatch.h"
#include "utils.h"

#ifndef __FF_NATIVE_NODE_UTILS_H__
#define __FF_NATIVE_NODE_UTILS_H__

namespace FF {

	struct SyncBinding {
	public:
		SyncBinding(std::shared_ptr<IWorker> worker, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
			run(worker, methodName, info);
		}

	private:
		void run(std::shared_ptr<IWorker> worker, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
			FF::TryCatch tryCatch(methodName);

			if (worker->applyUnwrappers(info)) {
				return tryCatch.reThrow();
			}

			std::string err = worker->execute();
			if (!err.empty()) {
				tryCatch.throwError(err);
				return;
			}

			info.GetReturnValue().Set(worker->getReturnValue());
		}
	};

	struct AsyncBinding {
	public:
		AsyncBinding(std::shared_ptr<IWorker> worker, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
			run(worker, methodName, info);
		}

	private:
		void run(std::shared_ptr<IWorker> worker, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
			FF::TryCatch tryCatch(methodName);
			if (!hasArg(info, info.Length() - 1) || !info[info.Length() - 1]->IsFunction()) {
				tryCatch.throwError("callback function required");
				return;
			}
			Nan::Callback *callback = new Nan::Callback(info[info.Length() - 1].As<v8::Function>());
			if (worker->applyUnwrappers(info)) {
				v8::Local<v8::Value> argv[] = { 
					Nan::Error(tryCatch.extendWithPrefix(tryCatch.getCaughtErrorMessageUnchecked()).c_str()), 
					Nan::Null() 
				};
				tryCatch.Reset();
				Nan::AsyncResource resource("native-node-utils:AsyncBinding::run");
				resource.runInAsyncScope(Nan::GetCurrentContext()->Global(), **callback, 2, argv);
				return;
			}
			Nan::AsyncQueueWorker(new FF::AsyncWorker(callback, worker));
		}
	};

}

#endif
