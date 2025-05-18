#define LOW(x)(x & 0xFFFFFFFF)
#define HIGH(x)(LOW(x >> 32))

void llmultiply(unsigned long long int l1, unsigned long long int l2, unsigned char *result)
{

    unsigned long int A_LOW = LOW(l1);
    unsigned long int A_HIGH = HIGH(l1);
    unsigned long int B_LOW = LOW(l2);
    unsigned long int B_HIGH = HIGH(l2);

    unsigned long int R0 = 0, R1 = 0, R2 = 0, R3 = 0;
    unsigned long long int tmp_res = 0;

    //a_low * b_low
    tmp_res = (unsigned long long int)A_LOW * B_LOW;
    R0 = LOW(tmp_res);
    R1 = HIGH(tmp_res);

    //a_low * b_high
    tmp_res = (unsigned long long int)A_LOW * B_HIGH;
    R1 += LOW(tmp_res);
    if (R1 < LOW(tmp_res)) 
        R2++;
    R2 += HIGH(tmp_res);
    if (R2 < HIGH(tmp_res))
        R3++;

    //a_high * b_low
    tmp_res = (unsigned long long int)A_HIGH * B_LOW;
    R1 += LOW(tmp_res);
    if (R1 < LOW(tmp_res))
        R2++;
    R2 += HIGH(tmp_res);
    if (R2 < HIGH(tmp_res))
        R3++;

    //a_high * b_high
    tmp_res = (unsigned long long int)A_HIGH * B_HIGH;
    R2 += LOW(tmp_res);
    if (R2 < LOW(tmp_res))
        R3++;
    R3 += HIGH(tmp_res);
    
    ((unsigned long int*)result)[0] = R0;
    ((unsigned long int*)result)[1] = R1;
    ((unsigned long int*)result)[2] = R2;
    ((unsigned long int*)result)[3] = R3;
}