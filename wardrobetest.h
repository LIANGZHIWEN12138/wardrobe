#include<cassert>
#include<wardrobe.h>
#include<iostream>
#include<ostream>


static const SSize TestWardrobeSize(50,100,120);
static const SSize TestCCompartmentSize1(50,40,20);
static const SSize TestCCompartmentSize2(50,6,60);
static const SSize TestCCompartmentErrorSize1(300,10,1);
static const SSize TestCCompartmentErrorSize2(3,100,120);
static const SSize TestCCompartmentErrorSize3(3,100,200);
static const SSize TestCCompartmentErrorSize4(3,300,100);
static const SSize TestClotheSize01(30,1,50);
static const SSize TestClotheSize02(50,10,3);
static const SSize TestOtherSize1(30,3,30);
static const SSize TestOtherSize2(30,5,10);

class CTest_Wardrobe
{
private:
    bool Mcoutflag = false;
public:
    CTest_Wardrobe();
    ~CTest_Wardrobe();
    CWardrobe wd;
    vector<CCompartment> vcpm;
    vector<CClothes> vclothe;
    vector<COthers> voth;
    void EnableCout();
    void DisableCout();
    void printsize(CObj &);
    void TestInit();
    void InitPartition();

    bool TestPartition(CWardrobe &wd, CCompartment &cpm, int startindex = 0);
    bool TestPartition(CWardrobe &wd, vector<CCompartment> &cpms, vector<int> startindexs);
    bool TestPartition(CWardrobe &wd, CCompartment &cpm, SSize startlxh = Gs0);
    bool TestPartition(CWardrobe &wd, vector<CCompartment> &cpms, vector<SSize> startlwhs);

    bool TestObjPutin(CWardrobe &wd, CCompartment &cpm, CThings &th);

    void SetUp(bool init_partition = false);
    void TearDown();
};
