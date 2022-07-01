#include "include/Include.h"

#include "include/TVSet.h"
#include "include/RemoteControl.h"

int main()
{
	TVSet tv;
	TVRemoteControl controller{ tv, std::cin, std::cout };

	while (controller.WorkflowGoesOn())
	{
		controller.HandleCommand();
	}

	std::cout << "Exiting program. Goodbye..." << std::endl;

	return 0;
}

