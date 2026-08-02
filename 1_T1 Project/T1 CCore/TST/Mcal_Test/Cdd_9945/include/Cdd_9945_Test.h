#ifndef CDD_9945_TEST_H_
#define CDD_9945_TEST_H_

typedef void (*Cdd9945func)(void);
typedef struct Cdd9945funcMachine
{
	unsigned short testid;
    Cdd9945func cddfunc;
} Cdd9945funcMachine;

//unsigned int cdd_9945_test_id_cur;
//unsigned int cdd_9945_test_id_last;

void cdd_9945_test_task(void);
void cdd_9945_0001(void);
void cdd_9945_0002(void);
void cdd_9945_0000_forspiinit(void);

void cdd_9945_test_0001(void);

// ---------- 9945-1 -------------------
 void cdd_9945_test_0101(void);
 void cdd_9945_test_0102(void);
 void cdd_9945_test_0103(void);
 void cdd_9945_test_0104(void);
 void cdd_9945_test_0105(void);
 void cdd_9945_test_0106(void);
 void cdd_9945_test_0107(void);
 void cdd_9945_test_0108(void);
 void cdd_9945_test_0109(void);
 void cdd_9945_test_0110(void);
 void cdd_9945_test_0111(void);
 void cdd_9945_test_0112(void);
 void cdd_9945_test_0113(void);
 void cdd_9945_test_0114(void);
 void cdd_9945_test_0115(void);
 void cdd_9945_test_0116(void);
 void cdd_9945_test_0117(void);
 void cdd_9945_test_0118(void);

// ---------- 9945-1 end----------------

// ---------- 9945-2 -------------------
void cdd_9945_test_0201(void);
void cdd_9945_test_0202(void);
void cdd_9945_test_0203(void);
void cdd_9945_test_0204(void);
void cdd_9945_test_0205(void);
void cdd_9945_test_0206(void);
void cdd_9945_test_0207(void);
void cdd_9945_test_0208(void);
void cdd_9945_test_0209(void);
void cdd_9945_test_0210(void);
void cdd_9945_test_0211(void);
void cdd_9945_test_0212(void);
void cdd_9945_test_0213(void);
void cdd_9945_test_0214(void);
void cdd_9945_test_0215(void);
void cdd_9945_test_0216(void);

void cdd_9945_test_0295(void);
void cdd_9945_test_0296(void);
void cdd_9945_test_0297(void);
void cdd_9945_test_0298(void);
void cdd_9945_test_0299(void);

//void cdd_9945_test_0223(void);
//void cdd_9945_test_0224(void);
//void cdd_9945_test_0225(void);
//void cdd_9945_test_0226(void);
//void cdd_9945_test_0227(void);
// ---------- 9945-2 end---------------

// ---------- 9945-3-------------------
void cdd_9945_test_0301(void);
void cdd_9945_test_0302(void);
void cdd_9945_test_0303(void);
void cdd_9945_test_0304(void);
void cdd_9945_test_0305(void);
void cdd_9945_test_0306(void);
void cdd_9945_test_0307(void);
void cdd_9945_test_0308(void);
void cdd_9945_test_0309(void);
// void cdd_9945_test_0310(void);
// void cdd_9945_test_0311(void);
// void cdd_9945_test_0312(void);
// void cdd_9945_test_0313(void);
// void cdd_9945_test_0314(void);
// void cdd_9945_test_0315(void);
// void cdd_9945_test_0316(void);
// void cdd_9945_test_0317(void);
// void cdd_9945_test_0318(void);
// void cdd_9945_test_0319(void);
// void cdd_9945_test_0320(void);
// void cdd_9945_test_0321(void);
// void cdd_9945_test_0322(void);

// ---------- 9945-3 end---------------

// ---------- 9945-4 ------------------
//void cdd_9945_test_0401(void);
//void cdd_9945_test_0402(void);
//void cdd_9945_test_0403(void);
//void cdd_9945_test_0404(void);
//void cdd_9945_test_0405(void);
//void cdd_9945_test_0406(void);
void cdd_9945_test_0407(void);
void cdd_9945_test_0408(void);
void cdd_9945_test_0409(void);
void cdd_9945_test_0410(void);
//void cdd_9945_test_0411(void);
//void cdd_9945_test_0412(void);
//void cdd_9945_test_0413(void);
//void cdd_9945_test_0414(void);
//void cdd_9945_test_0415(void);
//void cdd_9945_test_0416(void);
void cdd_9945_test_0417(void);
void cdd_9945_test_0418(void);
void cdd_9945_test_0419(void);
void cdd_9945_test_0420(void);
// ---------- 9945-4 end---------------

// ---------- 9945-5 ------------------
void cdd_9945_test_0501(void);
void cdd_9945_test_0502(void);
void cdd_9945_test_0503(void);
void cdd_9945_test_0504(void);
void cdd_9945_test_0505(void);
void cdd_9945_test_0506(void);
void cdd_9945_test_0507(void);
void cdd_9945_test_0508(void);
void cdd_9945_test_0509(void);
void cdd_9945_test_0510(void);
void cdd_9945_test_0511(void);
void cdd_9945_test_0512(void);
void cdd_9945_test_0513(void);
void cdd_9945_test_0514(void);
// ---------- 9945-5 end---------------

#endif /* CDD_9945_TEST_H_ */
