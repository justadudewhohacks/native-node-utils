#include <memory>
#include <nan.h>
#include <IWorker.h>

#ifndef __FF_ASYNCWORKER_H__
#define __FF_ASYNCWORKER_H__

namespace FF {

	class AsyncWorker : public Nan::AsyncWorker {
	public:
		std::shared_ptr<IWorker> worker;

		AsyncWorker(
			Nan::Callback* callback,
			std::shared_ptr<IWorker> worker
		) : Nan::AsyncWorker(callback), worker(worker) {}
		~AsyncWorker() {}

		void Execute() {
			std::string err = worker->execute();
			if (!std::string(err).empty()) {
				this->SetErrorMessage(err.c_str());
			}
		}

		void HandleOKCallback() {
			Nan::HandleScope scope;
			v8::Local<v8::Value> argv[] = { Nan::Null(), worker->getReturnValue() };
			callback->Call(2, argv);
		}

		void HandleErrorCallback() {
			Nan::HandleScope scope;
			v8::Local<v8::Value> argv[] = { Nan::New(this->ErrorMessage()).ToLocalChecked(), Nan::Null() };
			callback->Call(2, argv);
		}
	};

}

#endif