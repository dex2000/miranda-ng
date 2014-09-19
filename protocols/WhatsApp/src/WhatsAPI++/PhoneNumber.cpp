/*
 * PhoneNumber.cpp
 *
 */

#include "PhoneNumber.h"
#include "WAException.h"

struct CountryDescr
{
	char *name;
	int countryCode, mcc, mnc;
	char *ISO3166, *ISO639;
}
static countries[] =
{
	{ "Russia", 7, 250, 20, "RU", "ru" },
	{ "Kazakhstan", 7, 401, 77, "KZ", "kk" },
	{ "Afghanistan", 93, 412, 1, "AF", "ps" },
	{ "Albania", 355, 276, 1, "AL", "sq" },
	{ "Alberta", 1403, 302, 720, "CA", "en" },
	{ "Alberta", 1780, 302, 720, "CA", "en" },
	{ "Algeria", 213, 603, 1, "DZ", "ar" },
	{ "Andorra", 376, 213, 3, "AD", "ca" },
	{ "Angola", 244, 631, 2, "AO", "pt" },
	{ "Anguilla", 1264, 365, 10, "AI", "en" },
	{ "Antarctica (Australian bases)", 6721, 232, 1, "AQ", "en" },
	{ "Antigua and Barbuda", 1268, 344, 50, "AG", "en" },
	{ "Argentina", 54, 722, 10, "AR", "es" },
	{ "Armenia", 374, 283, 10, "AM", "hy" },
	{ "Aruba", 297, 363, 1, "AW", "nl" },
	{ "Ascension", 247, 658, 1, "AC", "en" },
	{ "Australia", 61, 505, 1, "AU", "en" },
	{ "Austria", 43, 232, 3, "AT", "de" },
	{ "Azerbaijan", 994, 400, 1, "AZ", "az" },
	{ "Bahamas", 1242, 364, 39, "BS", "en" },
	{ "Bahrain", 973, 426, 1, "BH", "ar" },
	{ "Bangladesh", 880, 470, 1, "BD", "bn" },
	{ "Barbados", 1246, 342, 750, "BB", "en" },
	{ "Belarus", 375, 257, 1, "BY", "be" },
	{ "Belgium", 32, 206, 1, "BE", "nl" },
	{ "Belize", 501, 702, 67, "BZ", "es" },
	{ "Benin", 229, 616, 1, "BJ", "fr" },
	{ "Bermuda", 1441, 350, 1, "BM", "en" },
	{ "Bhutan", 975, 402, 11, "BT", "dz" },
	{ "Bolivia", 591, 736, 1, "BO", "es" },
	{ "Bosnia and Herzegovina", 387, 218, 3, "BA", "bs" },
	{ "Botswana", 267, 652, 4, "BW", "en" },
	{ "Brazil", 55, 724, 2, "BR", "pt" },
	{ "British Columbia", 1250, 302, 720, "CA", "en" },
	{ "British Columbia", 1604, 302, 720, "CA", "en" },
	{ "British Columbia", 1778, 302, 720, "CA", "en" },
	{ "British Indian Ocean Territory", 246, 348, 1, "IO", "en" },
	{ "British Virgin Islands", 1284, 348, 170, "GB", "en" },
	{ "Brunei", 673, 528, 11, "BN", "ms" },
	{ "Bulgaria", 359, 284, 3, "BG", "bg" },
	{ "Burkina Faso", 226, 613, 1, "BF", "fr" },
	{ "Burundi", 257, 642, 82, "BI", "rn" },
	{ "Cambodia", 855, 456, 2, "KH", "km" },
	{ "Cameroon", 237, 624, 1, "CM", "fr" },
	{ "Cape Verde", 238, 625, 1, "CV", "pt" },
	{ "Cayman Islands", 1345, 346, 50, "GB", "en" },
	{ "Central African Republic", 236, 623, 3, "CF", "sg" },
	{ "Chad", 235, 622, 4, "TD", "fr" },
	{ "Chile", 56, 730, 2, "CL", "es" },
	{ "China", 86, 460, 3, "CN", "en" },
	{ "Colombia", 57, 732, 102, "CO", "es" },
	{ "Comoros", 269, 654, 1, "KM", "fr" },
	{ "Democratic Republic of the Congo", 243, 630, 1, "CD", "fr" },
	{ "Republic of the Congo", 242, 629, 1, "CG", "fr" },
	{ "Cook Islands", 682, 548, 1, "CK", "en" },
	{ "Costa Rica", 506, 658, 4, "CR", "es" },
	{ "Cote d'Ivoire", 712, 612, 1, "CI", "fr" },
	{ "Croatia", 385, 219, 1, "HR", "hr" },
	{ "Cuba", 53, 368, 1, "CU", "es" },
	{ "Cyprus", 357, 280, 1, "CY", "el" },
	{ "Czech Republic", 420, 230, 2, "CZ", "cs" },
	{ "Denmark", 45, 238, 1, "DK", "da" },
	{ "Djibouti", 253, 638, 1, "DJ", "fr" },
	{ "Dominica", 1767, 366, 20, "DM", "en" },
	{ "Dominican Republic", 1809, 370, 1, "DO", "es" },
	{ "Dominican Republic", 1829, 370, 1, "DO", "en" },
	{ "East Timor", 670, 514, 1, "TL", "pt" },
	{ "Ecuador", 593, 740, 0, "EC", "es" },
	{ "Egypt", 20, 602, 2, "EG", "ar" },
	{ "El Salvador", 503, 706, 1, "SV", "es" },
	{ "Equatorial Guinea", 240, 627, 3, "GQ", "es" },
	{ "Eritrea", 291, 657, 1, "ER", "ti" },
	{ "Estonia", 372, 248, 3, "EE", "et" },
	{ "Ethiopia", 251, 636, 11, "ET", "am" },
	{ "Falkland Islands", 500, 750, 1, "FK", "en" },
	{ "Faroe Islands", 298, 288, 2, "FO", "fo" },
	{ "Fiji", 679, 542, 1, "FJ", "en" },
	{ "Finland", 358, 244, 5, "FI", "fi" },
	{ "France", 33, 208, 9, "FR", "fr" },
	{ "French Guiana", 594, 742, 1, "GF", "fr" },
	{ "French Polynesia", 689, 547, 15, "PF", "fr" },
	{ "Gabon", 241, 628, 1, "GA", "fr" },
	{ "Gambia", 220, 607, 1, "GM", "en" },
	{ "Gaza Strip", 970, 0, 0, "PS", "ar" },
	{ "Georgia", 995, 282, 1, "GE", "ka" },
	{ "Germany", 49, 262, 1, "DE", "de" },
	{ "Ghana", 233, 620, 2, "GH", "ak" },
	{ "Gibraltar", 350, 266, 9, "GI", "en" },
	{ "Greece", 30, 202, 5, "GR", "el" },
	{ "Greenland", 299, 290, 1, "GL", "kl" },
	{ "Grenada", 1473, 352, 30, "GD", "en" },
	{ "Guadeloupe", 590, 340, 1, "GP", "fr" },
	{ "Guam", 1671, 535, 32, "GU", "en" },
	{ "Guatemala", 502, 704, 1, "GT", "es" },
	{ "Guinea", 224, 611, 1, "GN", "fr" },
	{ "Guinea-Bissau", 245, 632, 3, "GW", "pt" },
	{ "Guyana", 592, 738, 1, "GY", "pt" },
	{ "Haiti", 509, 372, 2, "HT", "fr" },
	{ "Honduras", 504, 708, 2, "HN", "es" },
	{ "Hong Kong", 852, 454, 0, "HK", "zh" },
	{ "Hungary", 36, 216, 70, "HU", "hu" },
	{ "Iceland", 354, 274, 2, "IS", "is" },
	{ "India", 91, 404, 30, "IN", "hi" },
	{ "Indonesia", 62, 510, 10, "ID", "id" },
	{ "Iraq", 964, 418, 20, "IQ", "ar" },
	{ "Iran", 98, 432, 35, "IR", "fa" },
	{ "Ireland (Eire)", 353, 272, 1, "IE", "en" },
	{ "Israel", 972, 425, 1, "IL", "he" },
	{ "Italy", 39, 222, 10, "IT", "it" },
	{ "Jamaica", 1876, 338, 50, "JM", "en" },
	{ "Japan", 81, 440, 1, "JP", "ja" },
	{ "Jordan", 962, 416, 77, "JO", "ar" },
	{ "Kenya", 254, 639, 7, "KE", "sw" },
	{ "Kiribati", 686, 545, 1, "KI", "en" },
	{ "Kuwait", 965, 419, 4, "KW", "ar" },
	{ "Kyrgyzstan", 996, 437, 1, "KG", "ky" },
	{ "Laos", 856, 457, 1, "LA", "lo" },
	{ "Latvia", 371, 247, 2, "LV", "lv" },
	{ "Lebanon", 961, 415, 1, "LB", "ar" },
	{ "Lesotho", 266, 651, 1, "LS", "st" },
	{ "Liberia", 231, 618, 7, "LR", "en" },
	{ "Libya", 218, 606, 0, "LY", "ar" },
	{ "Liechtenstein", 423, 295, 2, "LI", "de" },
	{ "Lithuania", 370, 246, 3, "LT", "lt" },
	{ "Luxembourg", 352, 270, 99, "LU", "fr" },
	{ "Macau", 853, 455, 2, "MO", "pt" },
	{ "Republic of Macedonia", 389, 294, 1, "MK", "mk" },
	{ "Madagascar", 261, 646, 2, "MG", "mg" },
	{ "Malawi", 265, 650, 1, "MW", "ny" },
	{ "Malaysia", 60, 502, 16, "MY", "en" },
	{ "Maldives", 960, 472, 1, "MV", "dv" },
	{ "Mali", 223, 610, 2, "ML", "fr" },
	{ "Malta", 356, 278, 1, "MT", "mt" },
	{ "Manitoba", 1204, 302, 720, "CA", "en" },
	{ "Marshall Islands", 692, 551, 1, "MH", "mh" },
	{ "Martinique", 596, 340, 1, "MQ", "fr" },
	{ "Mauritania", 222, 609, 2, "MR", "ar" },
	{ "Mauritius", 230, 617, 1, "MU", "en" },
	{ "Mayotte", 262, 654, 1, "YT", "fr" },
	{ "Mexico", 52, 334, 3, "MX", "es" },
	{ "Federated States of Micronesia", 691, 550, 1, "FM", "en" },
	{ "Moldova", 373, 259, 1, "MD", "ru" },
	{ "Monaco", 377, 212, 1, "MC", "fr" },
	{ "Mongolia", 976, 428, 91, "MN", "mn" },
	{ "Montenegro", 382, 297, 2, "ME", "sr" },
	{ "Montserrat", 1664, 354, 860, "MS", "en" },
	{ "Morocco", 212, 604, 0, "MA", "ar" },
	{ "Mozambique", 258, 643, 4, "MZ", "pt" },
	{ "Myanmar", 95, 414, 1, "MM", "my" },
	{ "Namibia", 264, 649, 3, "NA", "en" },
	{ "Nauru", 674, 536, 2, "NR", "na" },
	{ "Netherlands", 31, 204, 4, "NL", "nl" },
	{ "Netherlands Antilles", 599, 362, 51, "AN", "nl" },
	{ "Nepal", 977, 429, 1, "NP", "ne" },
	{ "New Brunswick", 1506, 302, 720, "CA", "en" },
	{ "New Caledonia", 687, 546, 1, "NC", "fr" },
	{ "New Zealand", 64, 530, 1, "NZ", "en" },
	{ "Newfoundland", 1709, 302, 720, "CA", "en" },
	{ "Nicaragua", 505, 710, 30, "NI", "es" },
	{ "Niger", 227, 614, 4, "NE", "fr" },
	{ "Nigeria", 234, 621, 20, "NG", "ha" },
	{ "Niue", 683, 555, 1, "NU", "en" },
	{ "Norfolk Island", 6723, 505, 10, "NF", "en" },
	{ "North Korea", 850, 467, 193, "KP", "ko" },
	{ "Northern Mariana Islands", 1670, 534, 1, "MP", "en" },
	{ "Northwest Territories", 1867, 302, 720, "CA", "en" },
	{ "Norway", 47, 242, 4, "NO", "nb" },
	{ "Nova Scotia", 1902, 302, 720, "CA", "en" },
	{ "Oman", 968, 422, 2, "OM", "ar" },
	{ "Ontario", 1416, 302, 720, "CA", "en" },
	{ "Ontario", 1519, 302, 720, "CA", "en" },
	{ "Ontario", 1613, 302, 720, "CA", "en" },
	{ "Ontario", 1647, 302, 720, "CA", "en" },
	{ "Ontario", 1705, 302, 720, "CA", "en" },
	{ "Ontario", 1807, 302, 720, "CA", "en" },
	{ "Ontario", 1905, 302, 720, "CA", "en" },
	{ "Pakistan", 92, 410, 1, "PK", "en" },
	{ "Palau", 680, 552, 80, "PW", "en" },
	{ "Palestine", 970, 425, 6, "PS", "ar" },
	{ "Panama", 507, 714, 2, "PA", "es" },
	{ "Papua New Guinea", 675, 537, 3, "PG", "ho" },
	{ "Paraguay", 595, 744, 6, "PY", "es" },
	{ "Peru", 51, 716, 6, "PE", "es" },
	{ "Philippines", 63, 515, 2, "PH", "fil" },
	{ "Poland", 48, 260, 3, "PL", "pl" },
	{ "Portugal", 351, 268, 1, "PT", "pt" },
	{ "Qatar", 974, 427, 2, "QA", "ar" },
	{ "Quebec", 1418, 302, 720, "CA", "en" },
	{ "Quebec", 1450, 302, 720, "CA", "en" },
	{ "Quebec", 1514, 302, 720, "CA", "en" },
	{ "Quebec", 1819, 302, 720, "CA", "en" },
	{ "Reunion", 262, 647, 0, "RE", "fr" },
	{ "Romania", 40, 226, 1, "RO", "ro" },
	{ "Rwanda", 250, 635, 10, "RW", "rw" },
	{ "Saint-Barthelemy", 590, 340, 1, "BL", "fr" },
	{ "Saint Helena", 290, 658, 1, "SH", "en" },
	{ "Saint Kitts and Nevis", 1869, 356, 50, "KN", "en" },
	{ "Saint Lucia", 1758, 358, 50, "LC", "en" },
	{ "Saint Martin (French side)", 590, 340, 1, "MF", "fr" },
	{ "Saint Pierre and Miquelon", 508, 308, 2, "PM", "fr" },
	{ "Saint Vincent and the Grenadines", 1670, 360, 70, "VC", "en" },
	{ "Samoa", 685, 549, 1, "WS", "sm" },
	{ "Sao Tome and Principe", 239, 626, 1, "ST", "pt" },
	{ "Saskatchewan", 1306, 302, 720, "CA", "en" },
	{ "Saudi Arabia", 966, 420, 4, "SA", "ar" },
	{ "Senegal", 221, 608, 1, "SN", "wo" },
	{ "Serbia", 381, 220, 1, "RS", "sr" },
	{ "Seychelles", 248, 633, 10, "SC", "fr" },
	{ "Sierra Leone", 232, 619, 4, "SL", "en" },
	{ "Singapore", 65, 525, 1, "SG", "en" },
	{ "Slovakia", 421, 231, 4, "SK", "sk" },
	{ "Slovenia", 386, 293, 31, "SI", "sl" },
	{ "Solomon Islands", 677, 540, 2, "SB", "en" },
	{ "Somalia", 252, 637, 82, "SO", "so" },
	{ "South Africa", 27, 655, 1, "ZA", "xh" },
	{ "South Korea", 82, 450, 5, "KR", "ko" },
	{ "South Sudan", 211, 659, 2, "SS", "en" },
	{ "Spain", 34, 214, 1, "ES", "es" },
	{ "Sri Lanka", 94, 413, 1, "LK", "si" },
	{ "Sudan", 249, 634, 7, "SD", "ar" },
	{ "Suriname", 597, 746, 3, "SR", "nl" },
	{ "Swaziland", 268, 653, 10, "SZ", "ss" },
	{ "Sweden", 46, 240, 7, "SE", "sv" },
	{ "Switzerland", 41, 228, 3, "CH", "de" },
	{ "Syria", 963, 417, 1, "SY", "ar" },
	{ "Taiwan", 886, 466, 1, "TW", "cmn" },
	{ "Tajikistan", 992, 436, 1, "TJ", "tg" },
	{ "Tanzania", 255, 640, 4, "TZ", "sw" },
	{ "Thailand", 66, 520, 0, "TH", "th" },
	{ "Togo", 228, 615, 1, "TG", "fr" },
	{ "Tokelau", 690, 690, 1, "TK", "tkl" },
	{ "Tonga", 676, 539, 1, "TO", "to" },
	{ "Trinidad and Tobago", 1868, 374, 12, "TT", "en" },
	{ "Tunisia", 216, 605, 1, "TN", "ar" },
	{ "Turkey", 90, 286, 2, "TR", "tr" },
	{ "Turkmenistan", 993, 438, 1, "TM", "tk" },
	{ "Turks and Caicos Islands", 1649, 376, 50, "TC", "en" },
	{ "Tuvalu", 688, 553, 1, "TV", "tvl" },
	{ "Uganda", 256, 641, 14, "UG", "sw" },
	{ "Ukraine", 380, 255, 1, "UA", "uk" },
	{ "United Arab Emirates", 971, 424, 2, "AE", "ar" },
	{ "United Kingdom", 44, 234, 10, "GB", "en" },
	{ "United States of America", 1, 310, 4, "US", "en" },
	{ "Uruguay", 598, 748, 7, "UY", "es" },
	{ "Uzbekistan", 998, 434, 7, "UZ", "uz" },
	{ "Vanuatu", 678, 541, 5, "VU", "bi" },
	{ "Venezuela", 58, 734, 4, "VE", "es" },
	{ "Vietnam", 84, 452, 1, "VN", "vi" },
	{ "U.S. Virgin Islands", 1340, 332, 4, "VI", "en" },
	{ "Wallis and Futuna", 681, 543, 1, "WF", "fr" },
	{ "West Bank", 970, 0, 1, "PS", "ar" },
	{ "Yemen", 967, 421, 2, "YE", "ar" },
	{ "Zambia", 260, 645, 2, "ZM", "en" },
	{ "Zimbabwe", 263, 648, 2, "ZW", "en" }
};

PhoneNumber::PhoneNumber(const std::string &szNumber)
{
	int cc1 = atoi(szNumber.substr(0, 1).c_str()), cc2 = atoi(szNumber.substr(0, 2).c_str()), cc3 = atoi(szNumber.substr(0, 3).c_str());

	for (int i = 0; i < _countof(countries); i++) {
		CountryDescr &p = countries[i];
		if (p.countryCode != cc1 && p.countryCode != cc2 && p.countryCode != cc3)
			continue;

		if (p.countryCode == 7)
			if (i == 0 && (cc2 == '77' || cc2 == '76'))
				continue;

		this->Country = p.name;
		this->countryCode = p.countryCode;
		this->Number = szNumber.substr(1 + (size_t)floor(log10(double(p.countryCode))));
		this->ISO3166 = p.ISO3166;
		this->ISO639 = p.ISO639;
		this->mcc = p.mcc;
		this->mnc = p.mnc;
		return;
	}

	throw new WAException("Could not dissect phone number " + szNumber);
}