#include "EventManager.hpp"

namespace mf
{
	EventManager::EventManager(sf::Vector2f *tPos, sf::Vector2f *tSize)
		: mPos(tPos), mSize(tSize)
	{
	}

	EventManager::~EventManager()
	{
	}

	void EventManager::Update(sf::Event &tEvent)
	{
		sf::Vector2i pos = sf::Vector2i(tEvent.mouseMove.x, tEvent.mouseMove.y);
		bool inside = (pos.x > mPos->x && pos.y > mPos->y && pos.x < mPos->x + mSize->x && pos.y < mPos->y + mSize->y);
		switch (tEvent.type)
		{
		case sf::Event::MouseMoved:
			if (inside && mEvent == eEvent::OUTSIDE)
				mEvent = eEvent::ENTERED;
			else if (inside || mEvent == eEvent::ENTERED)
				mEvent = eEvent::INSIDE;
			else if (!inside && mEvent == eEvent::INSIDE)
				mEvent = eEvent::EXITED;
			else if (!inside || mEvent == eEvent::EXITED)
				mEvent = eEvent::OUTSIDE;
			break;

		case sf::Event::MouseButtonPressed:
			if (mEvent == eEvent::ENTERED || mEvent == eEvent::INSIDE)
			{
				if (tEvent.mouseButton.button == sf::Mouse::Left)
					mEvent = eEvent::LEFT_CLICK;
				if (tEvent.mouseButton.button == sf::Mouse::Right)
					mEvent = eEvent::RIGHT_CLICK;
			}
		break;

		case sf::Event::MouseButtonReleased:
			if (mEvent == eEvent::ENTERED || mEvent == eEvent::INSIDE || mEvent == eEvent::LEFT_CLICK || mEvent == eEvent::RIGHT_CLICK)
			{
				if (tEvent.mouseButton.button == sf::Mouse::Left)
					mEvent = eEvent::LEFT_CLICK_RELEASE;
				if (tEvent.mouseButton.button == sf::Mouse::Right)
					mEvent = eEvent::RIGHT_CLICK_RELEASE;
			}
		break;

		default:
			mEvent = (inside) ? eEvent::INSIDE : eEvent::OUTSIDE;
			break;
		}

		if (mKeyListeners[(uint32_t)mEvent])
			mKeyListeners[(uint32_t)mEvent]();
	}

	void EventManager::AddEventListener(eEvent tEvent ,std::function<void()> tListener)
	{
		mKeyListeners[(uint32_t)tEvent] = tListener;
	}

} // namespace mf