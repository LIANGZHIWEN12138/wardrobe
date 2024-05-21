#include<wardrobetest.h>

CTest_Wardrobe::CTest_Wardrobe(){
    
}

CTest_Wardrobe::~CTest_Wardrobe(){
    
}

void CTest_Wardrobe::EnableCout(){
    Mcoutflag = true;
}

void CTest_Wardrobe::DisableCout(){
    Mcoutflag = false;
}

void CTest_Wardrobe::printsize(CObj &obj)
{
    SSize s = obj.GetSize();
    cout << "ID:" << obj.GetID() << "\tl:" << s.length << "\tw:" << s.width << "\th:" << s.height << endl;
}

void CTest_Wardrobe::TestInit(){
    vcpm = vector<CCompartment>(10);
    vclothe = vector<CClothes>(20);
    voth = vector<COthers>(10);
    SSize s,s1,s2;
    s = TestWardrobeSize;
    wd.Init(WDHID*100 + 1, s);
    s = TestCCompartmentSize1;
    vcpm[0].Init(CPMHID*100 + 1, s, PILE);//50*40*20 PILE
    vcpm[1].Init(CPMHID*100 + 2, s, PILE);//50*40*20 PILE
    s = TestCCompartmentSize2;
    vcpm[2].Init(CPMHID*100 + 3, s, HANG);//50*60*60 HANG
    vcpm[3].Init(CPMHID*100 + 4, s, HANG);//50*60*60 HANG
    s = TestCCompartmentErrorSize1;
    vcpm[4].Init(CPMHID*100 + 5, s);//300*10*1 HANG error can repair
    s = TestCCompartmentErrorSize2;
    vcpm[5].Init(CPMHID*100 + 6, s);//3*100*120 HANG error can repair
    s = TestCCompartmentErrorSize3;
    vcpm[6].Init(CPMHID*100 + 7, s);//3*100*200 HANG error
    s = TestCCompartmentErrorSize4;
    vcpm[7].Init(CPMHID*100 + 8, s);//3*300*100 HANG error
    s2 = TestClotheSize01;
    s1 = TestClotheSize02;
    for(int i = 0; i < 10; i++){
        vclothe[i].Init(CLTHHID*100 + i + 1, s1, s2 , UNFOLDED);//30*2*50 50*60*1  UNFOLDED
        vclothe[i + 10].Init(CLTHHID*100 + i + 11, s1, s2 , FOLDED);//30*2*50 50*60*1  FOLDED
    }
    s1 = TestOtherSize1;
    s2 = TestOtherSize2;
    for(int i = 0; i < 5; i++){
        voth[i].Init(OTHERHIS*100 + i + 1, s1);//30*3*30
        voth[i + 5].Init(OTHERHIS*100 + i + 6, s2);//30*5*10
    }
}

void CTest_Wardrobe::InitPartition(){
    wd.Partition(vcpm[0], 0);
    wd.Partition(vcpm[1], 20);
    wd.Partition(vcpm[2], 40);
    wd.Partition(vcpm[3], 120*50*60);
}

void CTest_Wardrobe::SetUp(bool init_partition){
    TestInit();
    if(init_partition){
        InitPartition();
    }
}


void CTest_Wardrobe::TearDown(){
    wd.Clear();
    vcpm.clear();
    vclothe.clear();
    voth.clear();
}


bool CTest_Wardrobe::TestPartition(CWardrobe &wd, CCompartment &cpm, int startindex){
    bool ret = wd.Partition(cpm, startindex);
    if(Mcoutflag){
        if(ret){
            cout << "Partition success." << endl;
            printsize(wd);
            printsize(cpm);
        }
        else{
            cout << "Partition failed." << endl;
            printsize(wd);
            printsize(cpm);
            cout << endl;
        }
    }
    return ret;
}

bool CTest_Wardrobe::TestPartition(CWardrobe &wd, vector<CCompartment> &cpms, vector<int> startindexs){
    bool ret = cpms.size() == startindexs.size();
    if(ret){
        for(int i = 0; i < cpms.size(); i++){
            ret &= wd.Partition(cpms[i], startindexs[i]);
            if(Mcoutflag){
                if(ret){
                    cout << "Partition:" << i << " success." << endl;
                    printsize(wd);
                    printsize(cpms[i]);
                }
                else{
                    cout << "Partition:" << i << " failed." << endl;
                    printsize(wd);
                    printsize(cpms[i]);
                    cout << endl;
                }
            }
        }
    }
    else{
        if(Mcoutflag){
            cout << "cpms and startindexs size not match." << endl;
            cout << "cpms size:" << cpms.size() << "\tstartindexs size:" << endl << startindexs.size();
        }
    }
    return ret;
}


bool CTest_Wardrobe::TestPartition(CWardrobe &wd, CCompartment &cpm, SSize startlxh){
    bool ret = wd.Partition(cpm, startlxh);
    if(Mcoutflag){
        if(ret){
            cout << "Partition success." << endl;
            printsize(wd);
            printsize(cpm);
        }
        else{
            cout << "Partition failed." << endl;
            printsize(wd);
            printsize(cpm);
            cout << endl;
        }
    }
    return ret;
}

bool CTest_Wardrobe::TestPartition(CWardrobe &wd, vector<CCompartment> &cpms, vector<SSize> startlwhs){
    bool ret = cpms.size() == startlwhs.size();
    if(ret){
        for(int i = 0; i < cpms.size(); i++){
            ret &= wd.Partition(cpms[i], startlwhs[i]);
            if(Mcoutflag){
                if(ret){
                    cout << "Partition:" << i << " success." << endl;
                    printsize(wd);
                    printsize(cpms[i]);
                    cout << endl;
                }
                else{
                    cout << "Partition:" << i << " failed." << endl;
                    printsize(wd);
                    printsize(cpms[i]);
                    cout << endl;
                }
            }
        }
    }
    else{
        if(Mcoutflag){
            cout << "cpms and startindexs size not match." << endl;
            cout << "cpms size:" << cpms.size() << "\tstartindexs size:" << startlwhs.size() << endl << endl;
        }
    }
    return ret;
}

bool CTest_Wardrobe::TestObjPutin(CWardrobe &wd, CCompartment &cpm, CThings &th){
    bool ret;
    ret = wd.ObjPutin(cpm, th);
    if(Mcoutflag){
        if(ret){
            cout << "PutIn success." << endl;
            printsize(cpm);
            printsize(th);
            cout << endl;
        }
        else{
            cout << "PutIn fail." << endl;
            printsize(cpm);
            printsize(th);
            cout << endl;
        }
    }
    return ret;
}





