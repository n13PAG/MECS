#pragma once

#include <memory>
#include <any>

namespace MECS {
	using EventID = unsigned int;

	class Event
	{
	public:
		Event(EventID type) {
			event_type_ = type;
		}

		template<typename T>
		void SetPackage(T value);

		template<typename T>
		T GetPackage();

		EventID GetType() {
			return event_type_;
		}

	private:
		EventID event_type_;
		std::any data_;
	};

	template<typename T>
	void Event::SetPackage(T value) {
		data_ = value;
	}

	template<typename T>
	T Event::GetPackage() {
		return std::any_cast<T>(data_);
	}
}