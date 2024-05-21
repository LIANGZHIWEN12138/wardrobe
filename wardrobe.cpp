#include<wardrobe.h>

CObj::CObj()
{

}

CObj::~CObj()
{

}

void CObj::Init(int id, int l, int w, int h)
{
    ID = id;
    SetSize(l, w, h);
}

void CObj::Init(int id, SSize &s)
{
    ID = id;
    SetSize(s);
}

int CObj::GetID(){
    return ID;
}

bool CObj::SetSize(int l, int w, int h)
{
    if(l <= 0 || w <= 0 || h <= 0){
        return false;
    }
    Mlength = l;
    Mwidth = w;
    Mheight = h;
    MN = l * w * h;
    return true;
}

bool CObj::SetSize(SSize &s)
{
    if(s.length <= 0 || s.width <= 0 || s.height <= 0){
        return false;
    }
    Mlength = s.length;
    Mwidth = s.width;
    Mheight = s.height;
    MN = s.length * s.width * s.height;
    return true;
}

bool CObj::GetSize(SSize &s)
{
    s.length = Mlength;
    s.width = Mwidth;
    s.height = Mheight;
    return true;
}

SSize CObj::GetSize()
{
    SSize s;
    s.length = Mlength;
    s.width = Mwidth;
    s.height = Mheight;
    return s;
}

void CThings::PutIn(){
    MPutFlag = true;
}

void CThings::Getout(){
    MPutFlag = false;
}

bool CThings::GetPutFlag()
{
    return MPutFlag;
}

int CThings::GetStatus()
{
    return Mstatus;
}

void CClothes::Init(int id, SSize &fs, SSize &ufs, bool status)
{
    ID = id;
    SetSize(fs,ufs);
    Mstatus = status;
    if(Mstatus == UNFOLDED){
        CObj::SetSize(ufs);
    }
    else if(Mstatus == FOLDED){
        CObj::SetSize(fs);
    }
}

bool CClothes::SetSize(SSize &fs, SSize &ufs)
{
    Mfoldedsize = fs;
    Munfoldedsize = ufs;
}

bool CClothes::folded2un()
{
    if(Mstatus == UNFOLDED && MPutFlag == false){
        return false;
    }
    else{
        if(CObj::SetSize(Munfoldedsize)){
            Mstatus = FOLDED;
            return true;
        }
        else{
            return false;
        }
    }
}

bool CClothes::un2folded()
{
    if(Mstatus == FOLDED && MPutFlag == false){
        return false;
    }
    else{
        if(CObj::SetSize(Mfoldedsize)){
            Mstatus = UNFOLDED;
            return true;
        }
        else{
            false;
        }
    }
}

bool CClothes::isfolded(){
    return Mstatus == FOLDED;
}

COthers::COthers(){
    Mstatus = CANNOTFOLDED;
}

bool CBlockBase::Init(int id, SSize &s)
{
    ID = id;
    if(SetSize(s)){
        Munitusage = vector<bool>(MN, false);
    }
}

bool CBlockBase::occupyunit(int n){
    bool ret = false;
    if(n >= 0 && n < MN){
        if(Munitusage[n] == false){
            Munitusage[n] = true;
            ret = true;
        }
    }
    return ret;
}

bool CBlockBase::occupyunits(vector<int> ns){
    bool ret = true;
    for(int n : ns){
        if(n < 0 || n >= MN){
            ret &= false;
        }
        else if(Munitusage[n] != false){
            ret &= false;
        }
    }
    if(ret == false){
        return ret;
    }
    for(int n : ns){
        Munitusage[n] = true;
    }
    return ret;
}

bool CBlockBase::releaseunit(int n){
    bool ret = false;
    if(n >= 0 && n < MN){
        if(Munitusage[n] == true){
            Munitusage[n] = false;
            ret = true;
        }
    }
    return ret;
}

bool CBlockBase::releaseunits(vector<int> ns){
    bool ret = true;
    for(int n : ns){
        if(n < 0 || n >= MN){
            ret &= false;
        }
        else if(Munitusage[n] == false){
            ret &= false;
        }
    }
    if(ret == false){
        return ret;
    }
    for(int n : ns){
        Munitusage[n] = false;
    }
    return ret;
}

int CCompartment::Gettype(){
    return Mtype;
}

void CCompartment::Init(int id, SSize &s, int type){
    ID = id;
    Mtype = type;
    if(SetSize(s)){
        Munitusage = vector<bool>(MN, false);
        if(Mtype == HANG){
            Mrest = Mwidth;
        }
        else if(Mtype == PILE){
            Mrest = Mheight;
        }
    }
}

bool CCompartment::ObjPutin(CThings &th){
    bool ret = false;
    if(Mtype == HANG && th.GetStatus() == UNFOLDED 
        && th.GetPutFlag() == false 
        && th.GetSize().height <= Mheight 
        && th.GetSize().width <= Mrest)
    {
        th.PutIn();
        Mrest -= th.GetSize().width;
        MContainObjs.emplace(th.GetID());
        ret = true;
    }
    else if(Mtype == PILE && (th.GetStatus() == FOLDED || th.GetStatus() == CANNOTFOLDED) 
        && th.GetPutFlag() == false 
        && th.GetSize().width <= Mwidth 
        && th.GetSize().height <= Mrest)
    {
        th.PutIn();
        Mrest -= th.GetSize().height;
        MContainObjs.emplace(th.GetID());
        ret = true;
    }
    return ret;
}

bool CCompartment::ObjGetout(CThings &th){
    bool ret = false;
    if(MContainObjs.count(th.GetID())){
        th.Getout();
        Mrest += th.GetSize().width;
        MContainObjs.erase(th.GetID());
        ret = true;
    }
    return ret;
}

void CWardrobe::index2wh(int i, int &w, int &h){
    if(i >= 0 && i < MN)
    {
        SSize lwh = index2lwh(i);
        w = lwh.width;
        h = lwh.height;
    }
}

void CWardrobe::index2lwh(int i,int &l, int &w, int &h){
    if(i >= 0 && i < MN)
    {
        SSize lwh = index2lwh(i);
        l = lwh.length;
        w = lwh.width;
        h = lwh.height;
    }
}

SSize CWardrobe::index2lwh(int i){
    SSize ret;
    if(i >= 0 && i < MN)
    {
        int w = i / (Mlength * Mheight);
        int l = (i - w * Mlength * Mheight) / Mheight;
        int h = i - w * Mlength * Mheight - l * Mheight;
        ret.length = l;
        ret.width = w;
        ret.height = h;
    }
    return ret;
}

void CWardrobe::lwh2index(int l, int w, int h, int &i)
{
    i = -1;
    if(l >= 0 && l < Mlength && w >= 0 && w < Mwidth && h >= 0 && h < Mheight)
    {
        i = w * Mlength * Mheight + l * Mheight + h;
    }
}

int CWardrobe::lwh2index(int l, int w, int h)
{
    int i = -1;
    if(l >= 0 && l < Mlength && w >= 0 && w < Mwidth && h >= 0 && h < Mheight)
    {
        i = w * Mlength * Mheight + l * Mheight + h;
    }
    return i;
}

void CWardrobe::lwh2index(SSize lwh, int &i)
{
    lwh2index(lwh.length, lwh.width, lwh.height, i);
}

int CWardrobe::lwh2index(SSize lwh)
{
    return lwh2index(lwh.length, lwh.width, lwh.height);
}


void CWardrobe::Clear(){
    MContainObjs.clear();
    Munitusage.clear();
    SetSize(0,0,0);
    MN = 0;
    Mrest = 0;
}

bool CWardrobe::ObjPutin(CCompartment &cpm, CThings &th){
    bool ret = false;
    if(MContainObjs.count(cpm.GetID())){
        ret = cpm.ObjPutin(th);
    }
    return ret;
}

bool CWardrobe::Partition(CCompartment &cpm, int startindex)
{
    SSize s = cpm.GetSize();
    SSize startlwh = index2lwh(startindex);
    return Partition(cpm, startlwh);
}

bool CWardrobe::Partition(CCompartment &cpm, SSize startlwh)
{
    SSize s = cpm.GetSize();
    s.length = Mlength;
    cpm.Init(cpm.GetID(), s, cpm.Gettype());
    bool ret = s.width <= Mwidth 
        && s.height <= Mheight 
        && lwh2index(startlwh) != -1 
        && s.length + startlwh.length <= Mlength 
        && s.width + startlwh.width <= Mwidth 
        && s.height + startlwh.height <= Mheight;
    if(!ret){
        return ret;
    }
    vector<int> occupyspace;
    for(int l = 0; l < s.length && ret == true; l++){
        for(int w = 0; w < s.width && ret == true; w++){
            for(int h = 0; h < s.height; h++){
                int i = lwh2index(l + startlwh.length, w + startlwh.width, h + startlwh.height);
                if(i >= 0 && i < MN){
                    ret &= !Munitusage[i];
                    occupyspace.push_back(i);
                }
                else{
                    ret = false;
                }
            }
        }
    }
    if(ret){
        MContainObjs.emplace(cpm.GetID());
        occupyunits(occupyspace);
    }
    return ret;
}

