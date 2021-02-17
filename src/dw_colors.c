#include "dw_colors.h"

#define CIE_rows 81
#define CIE_STRIDE 4
#define CIE_X 1
#define CIE_Y 2
#define CIE_Z 3
#define CIE_FIRST_LAMBDA 380
#define CIE_DELTA_LAMBDA 5


/**
 * CIE 1964 supplementary standard colorimetric observer
 * of spectral tristimulus values
 * Format: lambda, (X, Y, Z)
 * See here for more data:
 * http://cvrl.ioo.ucl.ac.uk/cmfs.htm
 */

static float CIE_data[] =
    {380, 0.000160, 0.000017, 0.000705,
     385, 0.000662, 0.000072, 0.002928,
     390, 0.002362, 0.000253, 0.010482,
     395, 0.007242, 0.000769, 0.032344,
     400, 0.019110, 0.002004, 0.086011,
     405, 0.043400, 0.004509, 0.197120,
     410, 0.084736, 0.008756, 0.389366,
     415, 0.140638, 0.014456, 0.656760,
     420, 0.204492, 0.021391, 0.972542,
     425, 0.264737, 0.029497, 1.282500,
     430, 0.314679, 0.038676, 1.553480,
     435, 0.357719, 0.049602, 1.798500,
     440, 0.383734, 0.062077, 1.967280,
     445, 0.386726, 0.074704, 2.027300,
     450, 0.370702, 0.089456, 1.994800,
     455, 0.342957, 0.106256, 1.900700,
     460, 0.302273, 0.128201, 1.745370,
     465, 0.254085, 0.152761, 1.554900,
     470, 0.195618, 0.185190, 1.317560,
     475, 0.132349, 0.219940, 1.030200,
     480, 0.080507, 0.253589, 0.772125,
     485, 0.041072, 0.297665, 0.570060,
     490, 0.016172, 0.339133, 0.415254,
     495, 0.005132, 0.395379, 0.302356,
     500, 0.003816, 0.460777, 0.218502,
     505, 0.015444, 0.531360, 0.159249,
     510, 0.037465, 0.606741, 0.112044,
     515, 0.071358, 0.685660, 0.082248,
     520, 0.117749, 0.761757, 0.060709,
     525, 0.172953, 0.823330, 0.043050,
     530, 0.236491, 0.875211, 0.030451,
     535, 0.304213, 0.923810, 0.020584,
     540, 0.376772, 0.961988, 0.013676,
     545, 0.451584, 0.982200, 0.007918,
     550, 0.529826, 0.991761, 0.003988,
     555, 0.616053, 0.999110, 0.001091,
     560, 0.705224, 0.997340, 0.000000,
     565, 0.793832, 0.982380, 0.000000,
     570, 0.878655, 0.955552, 0.000000,
     575, 0.951162, 0.915175, 0.000000,
     580, 1.014160, 0.868934, 0.000000,
     585, 1.074300, 0.825623, 0.000000,
     590, 1.118520, 0.777405, 0.000000,
     595, 1.134300, 0.720353, 0.000000,
     600, 1.123990, 0.658341, 0.000000,
     605, 1.089100, 0.593878, 0.000000,
     610, 1.030480, 0.527963, 0.000000,
     615, 0.950740, 0.461834, 0.000000,
     620, 0.856297, 0.398057, 0.000000,
     625, 0.754930, 0.339554, 0.000000,
     630, 0.647467, 0.283493, 0.000000,
     635, 0.535110, 0.228254, 0.000000,
     640, 0.431567, 0.179828, 0.000000,
     645, 0.343690, 0.140211, 0.000000,
     650, 0.268329, 0.107633, 0.000000,
     655, 0.204300, 0.081187, 0.000000,
     660, 0.152568, 0.060281, 0.000000,
     665, 0.112210, 0.044096, 0.000000,
     670, 0.081261, 0.031800, 0.000000,
     675, 0.057930, 0.022602, 0.000000,
     680, 0.040851, 0.015905, 0.000000,
     685, 0.028623, 0.011130, 0.000000,
     690, 0.019941, 0.007749, 0.000000,
     695, 0.013842, 0.005375, 0.000000,
     700, 0.009577, 0.003718, 0.000000,
     705, 0.006605, 0.002565, 0.000000,
     710, 0.004553, 0.001768, 0.000000,
     715, 0.003145, 0.001222, 0.000000,
     720, 0.002175, 0.000846, 0.000000,
     725, 0.001506, 0.000586, 0.000000,
     730, 0.001045, 0.000407, 0.000000,
     735, 0.000727, 0.000284, 0.000000,
     740, 0.000508, 0.000199, 0.000000,
     745, 0.000356, 0.000140, 0.000000,
     750, 0.000251, 0.000098, 0.000000,
     755, 0.000178, 0.000070, 0.000000,
     760, 0.000126, 0.000050, 0.000000,
     765, 0.000090, 0.000036, 0.000000,
     770, 0.000065, 0.000025, 0.000000,
     775, 0.000046, 0.000018, 0.000000,
     780, 0.000033, 0.000013, 0.000000};

DwXYZ * dw_XYZ_new()
{
    DwXYZ * C = malloc(sizeof(DwXYZ));
    C->X = 0;
    C->Y = 0;
    C->Z = 0;
    return C;
}
DwRGB * dw_RGB_new_from_lambda(double lambda)
{
    DwXYZ * C1 = dw_XYZ_new_from_lambda(lambda);
    DwRGB * C2 = dw_RGB_new_from_dw_XYZ(C1);
    free(C1);
    return C2;
}

static double inrange(double x)
{
    if(x < 0)
        return 0;
    if(x > 1)
        return 1;
    return x;
}

double gamma_corr(double x)
{
    if(x<= 0.0031308)
    {
        return 323.0*x/25.0;
    }
    return (211.0*pow(x, 5.0/12.0)-11.0)/200.0;
}

DwRGB * dw_RGB_new_from_dw_XYZ(DwXYZ * C)
{
    DwRGB * O = malloc(sizeof(DwRGB));
    // Linear conversion from XYZ to RGB
    O->R =  3.2404542*C->X - 1.5371385*C->Y - 0.4985314*C->Z;
    O->G = -0.9692660*C->X + 1.8760108*C->Y + 0.0415560*C->Z;
    O->B =  0.0556434*C->X - 0.2040259*C->Y + 1.0572252*C->Z;

    // cap
    O->R = inrange(O->R);
    O->G = inrange(O->G);
    O->B = inrange(O->B);

    // Convert to sRGB
    O->R = gamma_corr(O->R);
    O->G = gamma_corr(O->G);
    O->B = gamma_corr(O->B);

    return O;
}

DwXYZ * dw_XYZ_new_from_lambda(double lambda)
{
    // TODO: Interpolate the CIE table

    float row = (lambda-CIE_FIRST_LAMBDA)/CIE_DELTA_LAMBDA;
    int drow = round(row);

    DwXYZ * C = dw_XYZ_new();
    if(drow < 0 || drow > CIE_rows)
    {
        return C;
    }

    C->X = CIE_data[drow * CIE_STRIDE + CIE_X];
    C->Y = CIE_data[drow * CIE_STRIDE + CIE_Y];
    C->Z = CIE_data[drow * CIE_STRIDE + CIE_Z];

    return C;
}