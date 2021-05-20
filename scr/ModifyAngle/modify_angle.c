#include <avr/pgmspace.h>
#include <math.h>
#include "modify_angle.h"


/* Lookup table to avoid using trigonometry functions */
//const float lookuptable_cos_and_sin[46][2] PROGMEM = { { 1.0, 0.0 }, { 0.999847695156391, 0.017452406437284 }, { 0.999390827019096, 0.034899496702501 }, { 0.998629534754574, 0.052335956242944 }, { 0.997564050259824, 0.069756473744125 }, { 0.996194698091746, 0.087155742747658 }, { 0.994521895368273, 0.104528463267653 }, { 0.992546151641322, 0.121869343405147 }, { 0.99026806874157, 0.139173100960065 }, { 0.987688340595138, 0.156434465040231 }, { 0.984807753012208, 0.17364817766693 }, { 0.981627183447664, 0.190808995376545 }, { 0.978147600733806, 0.207911690817759 }, { 0.974370064785235, 0.224951054343865 }, { 0.970295726275996, 0.241921895599668 }, { 0.965925826289068, 0.258819045102521 }, { 0.961261695938319, 0.275637355816999 }, { 0.956304755963035, 0.292371704722737 }, { 0.951056516295153, 0.309016994374947 }, { 0.945518575599317, 0.325568154457157 }, { 0.939692620785908, 0.342020143325669 }, { 0.933580426497202, 0.3583679495453 }, { 0.927183854566787, 0.374606593415912 }, { 0.92050485345244, 0.390731128489274 }, { 0.913545457642601, 0.4067366430758 }, { 0.90630778703665, 0.422618261740699 }, { 0.898794046299167, 0.438371146789077 }, { 0.891006524188368, 0.453990499739547 }, { 0.882947592858927, 0.469471562785891 }, { 0.874619707139396, 0.484809620246337 }, { 0.866025403784439, 0.5 }, { 0.857167300702112, 0.515038074910054 }, { 0.848048096156426, 0.529919264233205 }, { 0.838670567945424, 0.544639035015027 }, { 0.829037572555042, 0.559192903470747 }, { 0.819152044288992, 0.573576436351046 }, { 0.809016994374947, 0.587785252292473 }, { 0.798635510047293, 0.601815023152048 }, { 0.788010753606722, 0.615661475325658 }, { 0.777145961456971, 0.629320391049837 }, { 0.766044443118978, 0.642787609686539 }, { 0.754709580222772, 0.656059028990507 }, { 0.743144825477394, 0.669130606358858 }, { 0.731353701619171, 0.681998360062498 }, { 0.719339800338651, 0.694658370458997 }, { 0.707106781186548, 0.707106781186548 } };	// Handling only one eighth or 45°
const float lookuptable_cos_and_sin[46][2] PROGMEM = { { 128.498039215686, 0}, { 128.47846834192, 2.24260000678615}, { 128.419761682097, 4.48451689588568}, { 128.321937118836, 6.72506775769624}, { 128.185024450446, 8.9635700987206}, { 128.009065381852, 11.1993420494608}, { 127.794113511891, 13.4317025721224}, { 127.540234316985, 15.6599716680646}, { 127.247505131196, 17.8834705849352}, { 126.91601512267, 20.1015220234245}, { 126.545865266475, 22.3134503435777}, { 126.137168313842, 24.518581770601}, { 125.690048757822, 26.7162446001001}, { 125.204642795364, 28.9057694026879}, { 124.681098285826, 31.0864892278993}, { 124.119574705937, 33.2577398073502}, { 123.520243101219, 35.4188597570808}, { 122.883286033885, 37.5691907790193}, { 122.208897527229, 39.7080778615055}, { 121.497283006521, 41.8348694788143}, { 120.748659236439, 43.9489177896164}, { 119.963254255035, 46.0495788343171}, { 119.141307304274, 48.1362127312125}, { 118.283068757161, 50.208183871404}, { 117.388800041471, 52.2648611124108}, { 116.458773560117, 54.3056179704216}, { 115.493272608176, 56.3298328111282}, { 114.492591286589, 58.3368890390813}, { 113.457034412582, 60.3261752855109}, { 112.38691742681, 62.2970855945558}, { 111.282566297273, 64.2490196078431}, { 110.144317420024, 66.1813827473637}, { 108.972517516697, 68.093586396586}, { 107.767523528893, 69.9850480797545}, { 106.529702509455, 71.8551916393175}, { 105.259431510656, 73.7034474114303}, { 103.957097469349, 75.5292523994803}, { 102.623097089097, 77.332050445581}, { 101.257836719339, 79.1112923999837}, { 99.8617322316101, 80.866436288353}, { 98.435208892861, 82.5969474768582}, { 96.9787012359199, 84.3022988350273}, { 95.4926529271286, 85.9819708963165}, { 93.9775166311975, 87.6354520163447}, { 92.4337538733199, 89.262238528745}, { 90.8618348985867, 90.8618348985867} };	// Handling only one eighth or 45°
const uint8_t lookuptable_arctan[65] PROGMEM = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 10, 11, 11, 12, 13, 14, 15, 16, 17, 17, 18, 19, 20, 21, 21, 22, 23, 24, 24, 25, 26, 27, 27, 28, 29, 29, 30, 31, 31, 32, 33, 33, 34, 35, 35, 36, 36, 37, 37, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45 };	// Resolution is good enough and a power of two
	
/* Helper lookup tables to save RAM and also to reduce stack overhead */
const uint8_t lookuptable_position_mirrowed_to_clockwise[] PROGMEM = { 1, 6, 0, 7, 2, 5, 3, 4};
const uint8_t lookuptable_position_clockwise_to_mirrowed[] PROGMEM = { 2, 0, 4, 6, 7, 5, 1, 3};


/* These are the customizable eight shifting directions */
uint16_t shifted_directions[8] =
{
	0,		// Mapping for direction Up
	60,		// Mapping for direction UpRight
	80,		// Mapping for direction Right
	135,	// Mapping for direction DownRight
	180,	// Mapping for direction Down
	225,	// Mapping for direction DownLeft
	280,	// Mapping for direction Left
	300		// Mapping for direction UpLeft
};


/*
 * The input values of the parameters are the summarized value for both axis, from -255 to +255, they are overwritten by the output
 * The output values of the parameters are depending on the used scaling of the lookup table
 */
void convert_and_shift_directions(int16_t* x, int16_t* y)
{
	int8_t eighth = 0;				// The eighth looking from top in clockwise rotation 2, 0, 4, 6, 7, 5, 1 & 3
	float precise_x, precise_y;		// The precise value for the axis
	uint8_t simple_x, simple_y;		// The simplified value for the axis
	uint16_t angle;					// The angle between x and y
	uint16_t length;				// The calculated width of the current shifting eighth or the length of the vector


	// Check parameter because this is called externally
	if (0 == x || 0 == y)
	{
		return;
	}


	// Get the eighth of the current position and only handle the eighth where x & y are greater than 0 and x is greater than y
	if (*x < 0)
	{
		eighth |= 1;

		simple_x = -*x;
	}
	else
	{
		simple_x = *x;
	}

	if (*y < 0)
	{
		eighth |= 4;

		simple_y = -*y;
	}
	else
	{
		simple_y = *y;
	}

	if (simple_y > simple_x)
	{
		eighth |= 2;

		simple_y ^= simple_x;
		simple_x ^= simple_y;
		simple_y ^= simple_x;
	}


	// Get the original angle in degree of the considered eighth
//	angle = simple_y * 45 / simple_x;											// Linear behavior of the lower axis compared to the higher one
//	angle = simple_y * 45 / (simple_y + simple_x);								// Some experimental summarized proportion
	angle = pgm_read_byte(&lookuptable_arctan[(simple_y << 6) / simple_x]);		// The real squared to circular angle


	// Now shift the angle depending on the given eight directions

	// Shift the representation of the eighth from the mirrored perspective to a clockwise orientation for easier shifting
	eighth = pgm_read_byte(&lookuptable_position_mirrowed_to_clockwise[eighth]);


	// Normalizing the direction for all eighth in a clockwise direction
	if (eighth % 2)
	{
		angle = 45 - angle;
	}


	// Handle the possible overlap of 360°
	if (eighth == 7)
	{
		length = 360 + shifted_directions[0];
	}
	else
	{
		length = shifted_directions[eighth + 1];
	}

	length -=  shifted_directions[eighth];


	// Calculate the new shifted angle within its eighth and its position (still clockwise)
	angle = angle * length / 45;
	angle += shifted_directions[eighth];

	eighth = angle / 45;
	angle %= 45;


	// De-normalizing the direction to get the mirroring effects back
	if (eighth % 2)
	{
		angle = 45 - angle;
	}


	// Calculate the length of the vector
	length = simple_x;		// Linear compared to the axis with the higher value
//	length = sqrt((uint32_t) simple_x * simple_x + (uint32_t) simple_y * simple_y);		// More precise and the correct value for the squared to circular transfoprmation, but way to slow


	// Update the position depending from the angle and length
	precise_x = pgm_read_float(&lookuptable_cos_and_sin[angle][0]) * length;
	precise_y = pgm_read_float(&lookuptable_cos_and_sin[angle][1]) * length;


	// Shift the representation of the eighth from clockwise orientation back to the mirrored perspective for easier handling
	eighth = pgm_read_byte(&lookuptable_position_clockwise_to_mirrowed[eighth]);


	// Handle the mirrored positions
	if (eighth & 2)
	{
		*x = (int16_t) precise_y;
		*y = (int16_t) precise_x;
	}
	else
	{
		*x = (int16_t) precise_x;
		*y = (int16_t) precise_y;
	}

	if (eighth & 1)
	{
		*x = -*x;
	}

	if (eighth & 4)
	{
		*y = -*y;
	}


	return;
}


void convert(int16_t* x, int16_t* y)
{
	int8_t eighth = 0;				// The eighth looking from top in clockwise rotation 2, 0, 4, 6, 7, 5, 1 & 3
	float precise_x, precise_y;		// The precise value for the axis
	uint8_t simple_x, simple_y;		// The simplified value for the axis
	uint16_t angle;					// The angle between x and y


	// Check parameter because this is called externally
	if (0 == x || 0 == y)
	{
		return;
	}


	// Get the eighth of the current position and only handle the eighth where x & y are greater than 0 and x is greater than y
	if (*x < 0)
	{
		eighth |= 1;

		simple_x = -*x;
	}
	else
	{
		simple_x = *x;
	}

	if (*y < 0)
	{
		eighth |= 4;

		simple_y = -*y;
	}
	else
	{
		simple_y = *y;
	}

	if (simple_y > simple_x)
	{
		eighth |= 2;

		simple_y ^= simple_x;
		simple_x ^= simple_y;
		simple_y ^= simple_x;
	}


	// Get the angle in degree of the considered eighth
	angle = simple_y * 45 / simple_x;


	// Update the position depending from the angle
	precise_x = pgm_read_float(&lookuptable_cos_and_sin[angle][0]) * simple_x;
	precise_y = pgm_read_float(&lookuptable_cos_and_sin[angle][1]) * simple_x;


	// Shift the calculated value to its real eighth
	if (eighth & 2)
	{
		*x = (int16_t) precise_y;
		*y = (int16_t) precise_x;
	}
	else
	{
		*x = (int16_t) precise_x;
		*y = (int16_t) precise_y;
	}

	if (eighth & 1)
	{
		*x = -*x;
	}

	if (eighth & 4)
	{
		*y = -*y;
	}


	return;
}
