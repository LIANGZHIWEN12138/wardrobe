#include<wardrobetest.h>

int main(){
    CWardrobe wd;
    vector<CCompartment> vcpm;
    vector<CClothes> vclothe;
    vector<COthers> voth;
    CTest_Wardrobe test;
    test.EnableCout();

    cout << "====================Partition Test====================" << endl;
    test.SetUp();
    assert(true == test.TestPartition(test.wd, test.vcpm[0], 10));
    test.TearDown();

    test.SetUp();
    assert(true == test.TestPartition(test.wd, test.vcpm[0], Gs0));
    test.TearDown();

    test.SetUp();
    assert(false == test.TestPartition(test.wd, test.vcpm[0], 599999));
    test.TearDown();

    test.SetUp();
    assert(false == test.TestPartition(test.wd, test.vcpm[0], SSize(49, 0, 0)));
    test.TearDown();

    test.SetUp();
    assert(true == test.TestPartition(test.wd, test.vcpm[4], 0));
    test.TearDown();

    test.SetUp();
    assert(true == test.TestPartition(test.wd, test.vcpm[5], 0));
    test.TearDown();

    test.SetUp();
    assert(false == test.TestPartition(test.wd, test.vcpm[6], 0));
    test.TearDown();

    test.SetUp();
    assert(false == test.TestPartition(test.wd, test.vcpm[7], 0));
    test.TearDown();

    cout << "====================End Partition Test====================" << endl << endl;


    cout << "====================Putin Test====================" << endl;
    test.SetUp(true);
    assert(false == test.TestObjPutin(test.wd, test.vcpm[0], test.vclothe[0]));
    assert(true == test.TestObjPutin(test.wd, test.vcpm[2], test.vclothe[1]));
    assert(false == test.TestObjPutin(test.wd, test.vcpm[0], test.vclothe[5]));
    assert(true == test.TestObjPutin(test.wd, test.vcpm[2], test.vclothe[6]));
    for(int i = 0; i < 10; i++){
        test.TestObjPutin(test.wd, test.vcpm[2], test.vclothe[i]);
    }
    assert(false == test.TestObjPutin(test.wd, test.vcpm[1], test.voth[0]));
    assert(false == test.TestObjPutin(test.wd, test.vcpm[3], test.voth[1]));
    assert(false == test.TestObjPutin(test.wd, test.vcpm[1], test.voth[2]));
    assert(false == test.TestObjPutin(test.wd, test.vcpm[3], test.voth[3]));
    assert(true == test.TestObjPutin(test.wd, test.vcpm[1], test.voth[5]));
    assert(false == test.TestObjPutin(test.wd, test.vcpm[3], test.voth[6]));
    assert(true == test.TestObjPutin(test.wd, test.vcpm[1], test.voth[7]));
    assert(false == test.TestObjPutin(test.wd, test.vcpm[3], test.voth[8]));
    test.TearDown();
    cout << "====================End Putin Test====================" << endl;
    

}