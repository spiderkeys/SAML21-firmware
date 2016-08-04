#pragma once

#if defined (__SAML21E15A__)
	#include "saml21a/include/saml21e15a.h"
#elif defined (__SAML21E16A__)
	#include "saml21a/include/saml21e16a.h"
#elif defined (__SAML21E17A__)
	#include "saml21a/include/saml21e17a.h"
#elif defined (__SAML21G16A__)
	#include "saml21a/include/saml21g16a.h"
#elif defined (__SAML21G17A__)
	#include "saml21a/include/saml21g17a.h"
#elif defined (__SAML21G18A__)
	#include "saml21a/include/saml21g18a.h"
#elif defined (__SAML21J16A__)
	#include "saml21a/include/saml21j16a.h"
#elif defined (__SAML21J17A__)
	#include "saml21a/include/saml21j17a.h"
#elif defined (__SAML21J18A__)
	#include "saml21a/include/saml21j18a.h"
#elif defined (__SAML21E15B__)
	#include "saml21b/include/saml21e15b.h"
#elif defined (__SAML21E16B__)
	#include "saml21b/include/saml21e16b.h"
#elif defined (__SAML21E17B__)
	#include "saml21b/include/saml21e17b.h"
#elif defined (__SAML21E18B__)
	#include "saml21b/include/saml21e18b.h"
#elif defined (__SAML21G16B__)
	#include "saml21b/include/saml21g16b.h"
#elif defined (__SAML21G17B__)
	#include "saml21b/include/saml21g17b.h"
#elif defined (__SAML21G18B__)
	#include "saml21b/include/saml21g18b.h"
#elif defined (__SAML21J16B__)
	#include "saml21b/include/saml21j16b.h"
#elif defined (__SAML21J17B__)
	#include "saml21b/include/saml21j17b.h"
#elif defined (__SAML21J18B__)
	#include "saml21b/include/saml21j18b.h"
#elif defined (__SAML21J18BU__)
	#include "saml21b/include/saml21j18bu.h"
#else
	#error No CMSIS implementation for device!
#endif
