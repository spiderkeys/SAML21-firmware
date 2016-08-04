#pragma once

// Helper macro
#define part_defined(part) (defined( __##part##__ ))


// ----------------------
// SAML family
// ----------------------

// Revision A
#define SAML21G18A 	( part_defined( SAML21G18A ) )
#define SAML21G16A 	( part_defined( SAML21G16A ) )
#define SAML21G17A 	( part_defined( SAML21G17A ) )
#define SAML21J18A 	( part_defined( SAML21J18A ) )
#define SAML21J17A 	( part_defined( SAML21J17A ) )
#define SAML21J16A 	( part_defined( SAML21J16A ) )
#define SAML21E15A 	( part_defined( SAML21E15A ) )
#define SAML21E16A 	( part_defined( SAML21E16A ) )
#define SAML21E17A 	( part_defined( SAML21E17A ) )

#define SAML21_REV_A (SAML21G18A || SAML21G16A || SAML21G17A || SAML21J18A || SAML21J17A || SAML21J16A || SAML21E15A || SAML21E16A || SAML21E17A)

// Revision B
#define SAML21E15B	( part_defined( SAML21E15B ) )
#define SAML21E16B	( part_defined( SAML21E16B ) )
#define SAML21E17B	( part_defined( SAML21E17B ) )
#define SAML21E18B	( part_defined( SAML21E18B ) )
#define SAML21G16B	( part_defined( SAML21G16B ) )
#define SAML21G17B	( part_defined( SAML21G17B ) )
#define SAML21G18B	( part_defined( SAML21G18B ) )
#define SAML21J16B	( part_defined( SAML21J16B ) )
#define SAML21J17B	( part_defined( SAML21J17B ) )
#define SAML21J18B	( part_defined( SAML21J18B ) )
#define SAML21J18BU	( part_defined( SAML21J18BU ) )

#define SAML21_REV_B (SAML21E15B || SAML21E16B || SAML21E17B || SAML21E18B || SAML21G16B || SAML21G17B || SAML21G18B || SAML21J16B || SAML21J17B || SAML21J18B || SAML21J18BU)

#define SAML_SERIES (SAML21_REV_A || SAML21_REV_B)

// ----------------------
// SAM Product Line
// ----------------------
#define SAM (SAML_SERIES)

// ----------------------
// Header inclusion
// ----------------------

#if SAML_SERIES
	#include "saml.h"
#endif