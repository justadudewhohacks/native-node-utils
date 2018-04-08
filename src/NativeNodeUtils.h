#include <nan.h>
#include <iostream>
#include "ArrayConverters.h"
#include "TypeConverters.h"
#include "AsyncWorker.h"
#include "IWorker.h"
#include "SimpleWorker.h"

#ifndef __FF_NATIVENODEUTILS_H__
#define __FF_NATIVENODEUTILS_H__

namespace FF {

	static std::string formatError(std::string methodName, std::string err) {
		return std::string(methodName) + std::string(" - ") + err;
	}

	class TryCatch : public Nan::TryCatch {
	public:
		v8::Local<v8::String> formatCatchedError(std::string methodName) {
			return Nan::New(
				formatError(
					std::string(methodName),
					*Nan::Utf8String(Exception()->ToString())
				)
			).ToLocalChecked();
		}

		void throwNew(v8::Local<v8::Value> err) {
			Reset();
			Nan::ThrowError(err);
			ReThrow();
		}
	};

	void SyncBinding(std::shared_ptr<IWorker> worker, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
		FF::TryCatch tryCatch;

		if (worker->applyUnwrappers(info)) {
			v8::Local<v8::Value> err = tryCatch.formatCatchedError(methodName);
			tryCatch.throwNew(err);
			return;
		}

		std::string err = worker->execute();
		if (!err.empty()) {
			tryCatch.throwNew(Nan::New(formatError(methodName, err)).ToLocalChecked());
			return;
		}

		info.GetReturnValue().Set(worker->getReturnValue());
	}

	void AsyncBinding(std::shared_ptr<IWorker> worker, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
		FF::TryCatch tryCatch;
		if (!hasArg(info.Length() - 1, info) || !info[info.Length() - 1]->IsFunction()) {
			tryCatch.throwNew(Nan::New(formatError(methodName, "callback function required")).ToLocalChecked());
			return;
		}
		Nan::Callback *callback = new Nan::Callback(info[info.Length() - 1].As<v8::Function>());
		if (worker->applyUnwrappers(info)) {
			v8::Local<v8::Value> argv[] = { Nan::Error(tryCatch.formatCatchedError(methodName)), Nan::Null() };
			tryCatch.Reset();
			callback->Call(2, argv);
			return;
		}
		Nan::AsyncQueueWorker(new FF::AsyncWorker(callback, worker));
	}

}

#endif