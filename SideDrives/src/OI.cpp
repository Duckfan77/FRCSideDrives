#include "OI.h"

#include <WPILib.h>

OI* OI::GetInstance()
{
	if(!m_instance)
		m_instance = new OI;
	return m_instance;
}

OI::OI() {
	// Process operator interface input here.
}
