
#ifdef _MSC_VER

static float fminf ( float a, float b )
{
    return _isnan(a) ? b : ( _isnan(b) ? a : ((a < b) ? a : b));
}

static float fmaxf ( float a, float b )
{
    return _isnan(a) ? b : ( _isnan(b) ? a : ((a > b) ? a : b));
}

static double fmin ( double a, double b )
{
    return _isnan(a) ? b : ( _isnan(b) ? a : ((a < b) ? a : b));
}

static double fmax ( double a, double b )
{
    return _isnan(a) ? b : ( _isnan(b) ? a : ((a > b) ? a : b));
}
#endif

