#include "Tables.hpp"

// THIS FILE WAS AUTOMATICALLY GENERATED
// CHANGES WILL BE LOST UPON REGENERATION

namespace Constants {
const OpmNum ln10 = OpmNum::Constant<0x23025850,0x92994045,0x68401799,0x14546843,0x64207601,0x10148862,0x87729760,0x33327900,0x96757261>(false, 0);const OpmNum ln2 = OpmNum::Constant<0x69314718,0x05599453,0x09417232,0x12145817,0x65680755,0x00134360,0x25525412,0x06800094,0x93393622>(false, -1);const OpmNum e = OpmNum::Constant<0x27182818,0x28459045,0x23536028,0x74713526,0x62497757,0x24709369,0x99595749,0x66967627,0x72407663>(false, 0);const OpmNum pi = OpmNum::Constant<0x31415926,0x53589793,0x23846264,0x33832795,0x02884197,0x16939937,0x51058209,0x74944592,0x30781641>(false, 0);const OpmNum half_pi = OpmNum::Constant<0x15707963,0x26794896,0x61923132,0x16916397,0x51442098,0x58469968,0x75529104,0x87472296,0x15390820>(false, 0);const OpmNum quart_pi = OpmNum::Constant<0x78539816,0x33974483,0x09615660,0x84581987,0x57210492,0x92349843,0x77645524,0x37361480,0x76954102>(false, -1);const OpmNum tau = OpmNum::Constant<0x62831853,0x07179586,0x47692528,0x67665590,0x05768394,0x33879875,0x02116419,0x49889184,0x61563281>(false, 0);const OpmNum one = OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, 0);const OpmNum one_half = OpmNum::Constant<0x50000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -1);}
namespace Tables {
const OpmNum lnTable[73] = 
{
	OpmNum::Constant<0x69314718,0x05599453,0x09417232,0x12145817,0x65680755,0x00134360,0x25525412,0x06800094,0x93393622>(false, -1),
	OpmNum::Constant<0x95310179,0x80432486,0x00439521,0x23280765,0x09222060,0x53653086,0x44199185,0x23980816,0x30010142>(false, -2),
	OpmNum::Constant<0x99503308,0x53168082,0x84821535,0x75442607,0x41688679,0x60994005,0x87978646,0x09559766,0x86666425>(false, -3),
	OpmNum::Constant<0x99950033,0x30835331,0x66809398,0x92053501,0x14607550,0x62393166,0x55199701,0x96668289,0x00324958>(false, -4),
	OpmNum::Constant<0x99995000,0x33330833,0x53331666,0x80951131,0x06348206,0x44010710,0x75512661,0x29432164,0x49160741>(false, -5),
	OpmNum::Constant<0x99999500,0x00333330,0x83335333,0x31666680,0x95225595,0x34920534,0x92154400,0x32107551,0x33040855>(false, -6),
	OpmNum::Constant<0x99999950,0x00003333,0x33083333,0x53333316,0x66668095,0x23684523,0x92063482,0x06350115,0x43928211>(false, -7),
	OpmNum::Constant<0x99999995,0x00000033,0x33333083,0x33335333,0x33316666,0x66809523,0x79702381,0x06349205,0x34920644>(false, -8),
	OpmNum::Constant<0x99999999,0x50000000,0x33333333,0x08333333,0x53333333,0x16666666,0x80952380,0x82738095,0x34920635>(false, -9),
	OpmNum::Constant<0x99999999,0x95000000,0x00333333,0x33308333,0x33335333,0x33333166,0x66666680,0x95238093,0x98809524>(false, -10),
	OpmNum::Constant<0x99999999,0x99500000,0x00003333,0x33333308,0x33333333,0x53333333,0x33166666,0x66668095,0x23809511>(false, -11),
	OpmNum::Constant<0x99999999,0x99950000,0x00000033,0x33333333,0x30833333,0x33335333,0x33333331,0x66666666,0x66809524>(false, -12),
	OpmNum::Constant<0x99999999,0x99995000,0x00000000,0x33333333,0x33330833,0x33333333,0x53333333,0x33331666,0x66666667>(false, -13),
	OpmNum::Constant<0x99999999,0x99999500,0x00000000,0x00333333,0x33333330,0x83333333,0x33335333,0x33333333,0x31666667>(false, -14),
	OpmNum::Constant<0x99999999,0x99999950,0x00000000,0x00003333,0x33333333,0x33083333,0x33333333,0x53333333,0x33333317>(false, -15),
	OpmNum::Constant<0x99999999,0x99999995,0x00000000,0x00000033,0x33333333,0x33333083,0x33333333,0x33335333,0x33333333>(false, -16),
	OpmNum::Constant<0x99999999,0x99999999,0x50000000,0x00000000,0x33333333,0x33333333,0x08333333,0x33333333,0x53333333>(false, -17),
	OpmNum::Constant<0x99999999,0x99999999,0x95000000,0x00000000,0x00333333,0x33333333,0x33308333,0x33333333,0x33335333>(false, -18),
	OpmNum::Constant<0x99999999,0x99999999,0x99500000,0x00000000,0x00003333,0x33333333,0x33333308,0x33333333,0x33333334>(false, -19),
	OpmNum::Constant<0x99999999,0x99999999,0x99950000,0x00000000,0x00000033,0x33333333,0x33333333,0x30833333,0x33333333>(false, -20),
	OpmNum::Constant<0x99999999,0x99999999,0x99995000,0x00000000,0x00000000,0x33333333,0x33333333,0x33330833,0x33333333>(false, -21),
	OpmNum::Constant<0x99999999,0x99999999,0x99999500,0x00000000,0x00000000,0x00333333,0x33333333,0x33333330,0x83333333>(false, -22),
	OpmNum::Constant<0x99999999,0x99999999,0x99999950,0x00000000,0x00000000,0x00003333,0x33333333,0x33333333,0x33083333>(false, -23),
	OpmNum::Constant<0x99999999,0x99999999,0x99999995,0x00000000,0x00000000,0x00000033,0x33333333,0x33333333,0x33333083>(false, -24),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x50000000,0x00000000,0x00000000,0x33333333,0x33333333,0x33333333>(false, -25),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x95000000,0x00000000,0x00000000,0x00333333,0x33333333,0x33333333>(false, -26),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99500000,0x00000000,0x00000000,0x00003333,0x33333333,0x33333333>(false, -27),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99950000,0x00000000,0x00000000,0x00000033,0x33333333,0x33333333>(false, -28),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99995000,0x00000000,0x00000000,0x00000000,0x33333333,0x33333333>(false, -29),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999500,0x00000000,0x00000000,0x00000000,0x00333333,0x33333333>(false, -30),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999950,0x00000000,0x00000000,0x00000000,0x00003333,0x33333333>(false, -31),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999995,0x00000000,0x00000000,0x00000000,0x00000033,0x33333333>(false, -32),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x50000000,0x00000000,0x00000000,0x00000000,0x33333333>(false, -33),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x95000000,0x00000000,0x00000000,0x00000000,0x00333333>(false, -34),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99500000,0x00000000,0x00000000,0x00000000,0x00003333>(false, -35),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99950000,0x00000000,0x00000000,0x00000000,0x00000033>(false, -36),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99995000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -37),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999500,0x00000000,0x00000000,0x00000000,0x00000000>(false, -38),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999950,0x00000000,0x00000000,0x00000000,0x00000000>(false, -39),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999995,0x00000000,0x00000000,0x00000000,0x00000000>(false, -40),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x50000000,0x00000000,0x00000000,0x00000000>(false, -41),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x95000000,0x00000000,0x00000000,0x00000000>(false, -42),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99500000,0x00000000,0x00000000,0x00000000>(false, -43),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99950000,0x00000000,0x00000000,0x00000000>(false, -44),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99995000,0x00000000,0x00000000,0x00000000>(false, -45),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999500,0x00000000,0x00000000,0x00000000>(false, -46),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999950,0x00000000,0x00000000,0x00000000>(false, -47),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999995,0x00000000,0x00000000,0x00000000>(false, -48),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x50000000,0x00000000,0x00000000>(false, -49),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x95000000,0x00000000,0x00000000>(false, -50),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99500000,0x00000000,0x00000000>(false, -51),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99950000,0x00000000,0x00000000>(false, -52),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99995000,0x00000000,0x00000000>(false, -53),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999500,0x00000000,0x00000000>(false, -54),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999950,0x00000000,0x00000000>(false, -55),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999995,0x00000000,0x00000000>(false, -56),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x50000000,0x00000000>(false, -57),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x95000000,0x00000000>(false, -58),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99500000,0x00000000>(false, -59),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99950000,0x00000000>(false, -60),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99995000,0x00000000>(false, -61),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999500,0x00000000>(false, -62),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999950,0x00000000>(false, -63),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999995,0x00000000>(false, -64),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x50000000>(false, -65),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x95000000>(false, -66),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99500000>(false, -67),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99950000>(false, -68),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99995000>(false, -69),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999500>(false, -70),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999950>(false, -71),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999995>(false, -72),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999>(false, -73)
};

const OpmNum atanTable[73] = 
{
	OpmNum::Constant<0x78539816,0x33974483,0x09615660,0x84581987,0x57210492,0x92349843,0x77645524,0x37361480,0x76954102>(false, -1),
	OpmNum::Constant<0x99668652,0x49116202,0x73784461,0x19878020,0x59024327,0x83225043,0x14648015,0x50877681,0x00277474>(false, -2),
	OpmNum::Constant<0x99996666,0x86665238,0x20634011,0x62092795,0x48561369,0x35254437,0x66396279,0x39418196,0x45655320>(false, -3),
	OpmNum::Constant<0x99999966,0x66668666,0x66523809,0x63492054,0x40116209,0x34554268,0x01309143,0x10481876,0x45472341>(false, -4),
	OpmNum::Constant<0x99999999,0x66666666,0x86666666,0x52380952,0x49206349,0x11544011,0x62093462,0x02679542,0x73836621>(false, -5),
	OpmNum::Constant<0x99999999,0x99666666,0x66668666,0x66666652,0x38095238,0x20634920,0x63401154,0x40116209,0x34620928>(false, -6),
	OpmNum::Constant<0x99999999,0x99996666,0x66666666,0x86666666,0x66665238,0x09523809,0x63492063,0x49205440,0x11544012>(false, -7),
	OpmNum::Constant<0x99999999,0x99999966,0x66666666,0x66668666,0x66666666,0x66523809,0x52380952,0x49206349,0x20634912>(false, -8),
	OpmNum::Constant<0x99999999,0x99999999,0x66666666,0x66666666,0x86666666,0x66666666,0x52380952,0x38095238,0x20634921>(false, -9),
	OpmNum::Constant<0x99999999,0x99999999,0x99666666,0x66666666,0x66668666,0x66666666,0x66666652,0x38095238,0x09523810>(false, -10),
	OpmNum::Constant<0x99999999,0x99999999,0x99996666,0x66666666,0x66666666,0x86666666,0x66666666,0x66665238,0x09523810>(false, -11),
	OpmNum::Constant<0x99999999,0x99999999,0x99999966,0x66666666,0x66666666,0x66668666,0x66666666,0x66666666,0x66523809>(false, -12),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x66666666,0x66666666,0x66666666,0x86666666,0x66666666,0x66666667>(false, -13),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99666666,0x66666666,0x66666666,0x66668666,0x66666666,0x66666667>(false, -14),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99996666,0x66666666,0x66666666,0x66666666,0x86666666,0x66666667>(false, -15),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999966,0x66666666,0x66666666,0x66666666,0x66668666,0x66666667>(false, -16),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x66666666,0x66666666,0x66666666,0x66666666,0x86666667>(false, -17),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99666666,0x66666666,0x66666666,0x66666666,0x66668667>(false, -18),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99996666,0x66666666,0x66666666,0x66666666,0x66666667>(false, -19),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999966,0x66666666,0x66666666,0x66666666,0x66666667>(false, -20),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x66666666,0x66666666,0x66666666,0x66666667>(false, -21),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99666666,0x66666666,0x66666666,0x66666667>(false, -22),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99996666,0x66666666,0x66666666,0x66666667>(false, -23),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999966,0x66666666,0x66666666,0x66666667>(false, -24),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x66666666,0x66666666,0x66666667>(false, -25),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99666666,0x66666666,0x66666667>(false, -26),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99996666,0x66666666,0x66666667>(false, -27),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999966,0x66666666,0x66666667>(false, -28),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x66666666,0x66666667>(false, -29),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99666666,0x66666667>(false, -30),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99996666,0x66666667>(false, -31),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999966,0x66666667>(false, -32),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x66666667>(false, -33),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99666667>(false, -34),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99996667>(false, -35),
	OpmNum::Constant<0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999999,0x99999967>(false, -36),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -36),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -37),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -38),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -39),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -40),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -41),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -42),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -43),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -44),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -45),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -46),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -47),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -48),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -49),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -50),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -51),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -52),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -53),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -54),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -55),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -56),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -57),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -58),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -59),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -60),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -61),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -62),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -63),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -64),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -65),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -66),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -67),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -68),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -69),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -70),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -71),
	OpmNum::Constant<0x10000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000>(false, -72)
};

}