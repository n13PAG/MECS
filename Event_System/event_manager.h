#pragma once

#include "event.h"
#include "listener.h"

#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>


namespace MECS {
	class EventManager {
	public:
		template<typename T>
		Event CreateEvent(EventID event_id, T data) {
			Event event(event_id);
			event.SetPackage(data);
			return event;
		}

		void AddListener(EventID event_id, IListener* listener) {
			listeners_[event_id].push_back(listener);
		}

		void RemoveListener(EventID event_id, IListener* listener) {
			std::vector<IListener*>::iterator iter = std::find(listeners_[event_id].begin(), listeners_[event_id].end(), listener);
			if (iter != listeners_[event_id].end()) {
				listeners_[event_id].erase(iter);
			}
		}

		void InvokeEvent(EventID event_id) {
			Event event(event_id);

			for (const auto& listener : listeners_[event_id]) {
				listener->Listen(event);
			}
		}

		void InvokeEvent(Event& event) {
			for (const auto& listener : listeners_[event.GetType()]) {
				listener->Listen(event);
			}
		}


	private:
		std::unordered_map<EventID, std::vector<IListener*>> listeners_;
	};
}