#include "podf.h"

PODF PODF_Vy, PODF_Vx, PODF_W;

float podf_cal(PODF* podf)
{
    float t;
    t = millis;
    if(t < podf->t1)
    {
        t = millis;
//位置
        podf->q_t = podf->a0	+	podf->a1 * (t - podf->t0) +
                    podf->a2 * (t - podf->t0) * (t - podf->t0) + 
                    podf->a3 * (t - podf->t0) * (t - podf->t0) * (t - podf->t0) +
                    podf->a4 * (t - podf->t0) * (t - podf->t0) * (t - podf->t0) * (t - podf->t0) +
                    podf->a5 * (t - podf->t0) * (t - podf->t0) * (t - podf->t0) * (t - podf->t0) * (t - podf->t0);
//速度
        podf->v_t =	1 * podf->a1 +
                    2 * podf->a2 * (t - podf->t0) +
                    3 * podf->a3 * (t - podf->t0) * (t - podf->t0)+
                    4 * podf->a4 * (t - podf->t0) * (t - podf->t0) * (t - podf->t0)+
                    5 * podf->a5 * (t - podf->t0) * (t - podf->t0) * (t - podf->t0) * (t - podf->t0);

//加速度
        podf->acc_t = 2 * podf->a2 +
                      3 * podf->a3 * (t - podf->t0) +
                      4 * podf->a4 * (t - podf->t0) * (t - podf->t0) +
                      5 * podf->a5 * (t - podf->t0) * (t - podf->t0) * (t - podf->t0);
        return podf->v_t;
    }
    else
	{		
		return 0;
	}

}

void podf_reinit(PODF* podf, float q0, float q1, float v0, float v1, float acc0, float acc1, float t0, float t1)
{
    volatile float h, T;
    h = q1 - q0;
    T = t1 - t0;
    podf->t0 = t0;
    podf->t1 = t1;
    podf->a0 = q0;
    podf->a1 = v0;
    podf->a2 = 1.0 / 2 * acc0;
    podf->a3 = 1.0 / (2 * T * T * T) * (20 * h - (8 * v1 + 12 * v0) * T + (acc1 - 3 * acc0) / (T * T));
    podf->a4 = 1.0 / (2 * T * T * T * T) * (-30 * h + (14 * v1 + 16 * v0) * T + (3 * acc0 - 2 * acc1) / (T * T));
    podf->a5 = 1.0 / (2 * T * T * T * T * T) * (12 * h - 6 * (v1 + v0) * T + (acc1 - acc0) / (T * T));
}
