/*!
	@file
	@author		Albert Semenov
	@date		08/2009
*/
#ifndef GRAPH_NODE_WEIGHT_H_
#define GRAPH_NODE_WEIGHT_H_

#include <MyGUI.h>
#include "BaseAnimationNode.h"
#include "WeightController.h"

namespace demo
{

	class GraphNodeWeightController :
		public BaseAnimationNode
	{
	public:
		GraphNodeWeightController(const std::string& _name) :
			BaseAnimationNode("GraphNodeWeight.layout", "WeightController", _name),
			mConnectionOut(nullptr),
			mEditPosition(nullptr),
			mScrollPosition(nullptr),
			mPosition(0)
		{
		}

		void addConnection(const std::string& _eventout, BaseAnimationNode* _node, const std::string& _eventin) override
		{
			BaseAnimationNode::addConnection(_eventout, _node, _eventin);
			onChangePosition(mPosition);
		}

	private:
		void initialise() override
		{
			mMainWidget->castType<MyGUI::Window>()->setCaption(getName());
			assignBase(mConnectionOut, "ConnectionOut");
			assignWidget(mEditPosition, "EditPosition");
			assignWidget(mScrollPosition, "ScrollPosition");

			mEditPosition->eventEditSelectAccept += MyGUI::newDelegate(this, &GraphNodeWeightController::notifyEditSelectAccept);
			mScrollPosition->eventScrollChangePosition += MyGUI::newDelegate(this, &GraphNodeWeightController::notifyScrollChangePosition);

			updateWidgets();
		}

		void shutdown() override
		{
		}

		void updateWidgets(bool _edit = true, bool _scroll = true)
		{
			if (_edit)
			{
				mEditPosition->setCaption(MyGUI::utility::toString(mPosition));
			}
			if (_scroll)
			{
				double range = (double)mScrollPosition->getScrollRange() - 1;
				mScrollPosition->setScrollPosition((size_t)((range * (double)mPosition)));
			}

			onChangePosition(mPosition);
		}

		void notifyEditSelectAccept(MyGUI::EditBox* _sender)
		{
			mPosition = MyGUI::utility::parseValue<float>(_sender->getCaption());
			if (mPosition < 0) mPosition = 0;
			else if (mPosition > 1) mPosition = 1;

			updateWidgets();
		}

		void notifyScrollChangePosition(MyGUI::ScrollBar* _sender, size_t _position)
		{
			double range = (double)_sender->getScrollRange() - 1;
			double position = (double)_position;

			mPosition = (float)(position / range);
			updateWidgets(true, false);
		}

		void onChangePosition(float _position)
		{
			animation::WeightController* controller = dynamic_cast<animation::WeightController*>(getAnimationNode());
			if (controller)
				controller->generateEvent(_position);
		}

	private:
		wraps::BaseGraphConnection* mConnectionOut;
		MyGUI::EditBox* mEditPosition;
		MyGUI::ScrollBar* mScrollPosition;
		float mPosition;

	};

} // namespace demo

#endif // GRAPH_NODE_WEIGHT_H_
