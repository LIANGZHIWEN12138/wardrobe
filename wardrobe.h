#ifndef WARDROBE_HH
#define WARDROBE_HH
#include<set>
#include<vector>
using namespace std;

struct SSize
{
    int length = 0;
    int width = 0;
    int height = 0;
    SSize(int l = 0, int w = 0, int h = 0):length(l),width(w),height(h){}
};

static SSize Gs0;
#define FOLDED          1
#define UNFOLDED        0
#define CANNOTFOLDED    -1
#define HANG            0
#define PILE            1


#define WDHID 100
#define CPMHID  101
#define THHID  200
#define CLTHHID  201
#define OTHERHIS  202

class CObj
{
protected:
    int ID = -1;
    int Mlength = -1;
    int Mwidth = -1;
    int Mheight = -1;
    int MN = -1;
public:
    CObj();
    ~CObj();
    void Init(int id, int l = 0, int w = 0, int h = 0);
    void Init(int id, SSize &s = Gs0);
    int GetID();
    bool SetSize(int l, int w, int h);
    bool SetSize(SSize &s);
    bool GetSize(SSize &s);
    SSize GetSize();
};



class CThings : public CObj
{
protected:
    bool MPutFlag = false;
    int Mstatus = CANNOTFOLDED;
public:
    void PutIn();
    void Getout();
    bool GetPutFlag();
    int GetStatus();
};



class CClothes : public CThings
{
protected:
    SSize Mfoldedsize;
    SSize Munfoldedsize;
    bool SetSize(SSize &fs, SSize &ufs);
public:
    void Init(int id, SSize &fs, SSize &ufs, bool status = UNFOLDED);
    bool folded2un();
    bool un2folded();
    bool isfolded();
};



class COthers : public CThings
{
protected:
public:
    COthers();
};



class CBlockBase : public CObj
{
protected:
    int Mrest = -1;
    set<int> MContainObjs;
    vector<bool> Munitusage;
    bool occupyunit(int n);
    bool occupyunits(vector<int> ns);
    bool releaseunit(int n);
    bool releaseunits(vector<int> ns);
public:
    CBlockBase(){}
    ~CBlockBase(){}
    bool Init(int id, SSize &s);
    // bool ObjPutin(){}
    // bool ObjGetout(){}
};



class CCompartment : public CBlockBase
{
protected:
    int Mtype = -1;
public:
    int Gettype();
    void Init(int id, SSize &s, int type = PILE);
    bool ObjPutin(CThings &th);
    // bool ObjGetout(int thid);
    bool ObjGetout(CThings &th);
    // friend class CWardrobe;
};



class CWardrobe : public CBlockBase
{
private:
    void index2wh(int i, int &w, int &h);
    void index2lwh(int i, int &l, int &w, int &h);
    SSize index2lwh(int i);
    void lwh2index(int l, int w, int h, int &i);
    int lwh2index(int l, int w, int h);
    void lwh2index(SSize lwh, int &i);
    int lwh2index(SSize lwh);
public:
    void Clear();
    bool ObjPutin(CCompartment &cpm, CThings &th);
    bool Partition(CCompartment &cpm, int startindex);
    bool Partition(CCompartment &cpm, SSize startindex);
    // friend class CCompartment;
};

#endif





