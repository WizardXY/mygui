#ifndef GROUP_2_CONTROLLER_H_
#define GROUP_2_CONTROLLER_H_

#include "IAnimationNode.h"
#include "IAnimationGraph.h"
#include "ConnectionReceiver.h"

namespace animation
{

	class Group2Controller :
		public IAnimationNode
	{
	public:
		Group2Controller()
		{
		}

		Group2Controller(const std::string& _name, IAnimationGraph* _graph) :
			IAnimationNode(_name, _graph)
		{
		}

		~Group2Controller() override
		{
		}

		void setEvent(const std::string& _name, float _value) override
		{
			if (_name == "Start1") startAnimation1();
			else if (_name == "Start2") startAnimation2();
		}

		void addConnection(const std::string& _eventout, IAnimationNode* _node, const std::string& _eventin) override
		{
			mConnection.addConnection(_eventout, _node, _eventin);
		}

		void removeConnection(const std::string& _eventout, IAnimationNode* _node, const std::string& _eventin) override
		{
			mConnection.removeConnection(_eventout, _node, _eventin);
		}

	private:
		void startAnimation1()
		{
			mConnection.forceEvent("Stop2");
			mConnection.forceEvent("Start1");
		}

		void startAnimation2()
		{
			mConnection.forceEvent("Stop1");
			mConnection.forceEvent("Start2");
		}

	private:
		ConnectionReceiver mConnection;

	};

} // namespace animation

#endif // GROUP_2_CONTROLLER_H_
