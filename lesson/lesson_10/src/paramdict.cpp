#include "paramdict.h"
#include <stdio.h>
#include <iostream>
#include "datareader.h"
using namespace std;

namespace ncnn {

ParamDict::ParamDict() { clear(); }
int ParamDict::get(int id, int def) const { return params[id].type ? params[id].i : def; }
float ParamDict::get(int id, float def) const { return params[id].type ? params[id].f : def; }
Mat ParamDict::get(int id, const Mat& def) const { return params[id].type ? params[id].v : def; }

static bool vstr_is_float(const char vstr[16]) {
    // look ahead for determine isfloat
    for (int j = 0; j < 16; j++) {
        if (vstr[j] == '\0') break;

        if (vstr[j] == '.' || tolower(vstr[j]) == 'e') return true;
    }

    return false;
}

void ParamDict::clear() {
    for (int i = 0; i < NCNN_MAX_PARAM_COUNT; i++) {
        params[i].type = 0;
    }
}

static float vstr_to_float(const char vstr[16]) {
    double v = 0.0;

    const char* p = vstr;

    // sign
    bool sign = *p != '-';
    if (*p == '+' || *p == '-') {
        p++;
    }

    // digits before decimal point or exponent
    unsigned int v1 = 0;
    while (isdigit(*p)) {
        v1 = v1 * 10 + (*p - '0');
        p++;
    }

    v = (double)v1;

    // digits after decimal point
    if (*p == '.') {
        p++;

        unsigned int pow10 = 1;
        unsigned int v2 = 0;

        while (isdigit(*p)) {
            v2 = v2 * 10 + (*p - '0');
            pow10 *= 10;
            p++;
        }

        v += v2 / (double)pow10;
    }

    // exponent
    if (*p == 'e' || *p == 'E') {
        p++;

        // sign of exponent
        bool fact = *p != '-';
        if (*p == '+' || *p == '-') {
            p++;
        }

        // digits of exponent
        unsigned int expon = 0;
        while (isdigit(*p)) {
            expon = expon * 10 + (*p - '0');
            p++;
        }

        double scale = 1.0;
        while (expon >= 8) {
            scale *= 1e8;
            expon -= 8;
        }
        while (expon > 0) {
            scale *= 10.0;
            expon -= 1;
        }

        v = fact ? v * scale : v / scale;
    }

    //     fprintf(stderr, "v = %f\n", v);
    return sign ? (float)v : (float)-v;
}

int ParamDict::load_param(const DataReader& dr) {
    clear();
    int id = 0;
    while (dr.scan("%d=", &id) == 1) {
        bool is_array = id <= -23300;
        if (is_array) {
            id = -id - 23300;
        }
        if (is_array) {
            int a = 0;
        } else {
            char vstr[16];
            int nscan = dr.scan("%15s", vstr);

            bool is_float = vstr_is_float(vstr);
            if (is_float)
                params[id].f = vstr_to_float(vstr);
            else
                nscan = sscanf(vstr, "%d", &params[id].i);

            params[id].type = is_float ? 3 : 2;
        }
    }
    return 0;
}
}
