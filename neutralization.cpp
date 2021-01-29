// 化学 中和反応
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<tuple>
#include<cstdint>
#include<cstdio>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<deque>
#include<unordered_map>
#include<unordered_set>
#include<bitset>
#include<cctype>
using namespace std;
#define ll int64_t

// 酸性の価数を返す
int valence_acid_fn(string material_acid){
  int valence;
  // 酢酸の場合
  if(material_acid=="CH3COOH"){
    valence=1;
    return valence;
  }
  // その他
  else{
    // 1価
    if(material_acid=="HCl" || material_acid=="HNO3"){
      valence=1;
      return valence;
    }
    // それ以外
    else{
      valence=(int)material_acid.at(1)-48;
      return valence;
    }
  }
}

// 塩基の価数を返す
int valence_base_fn(string material_base){
  int valence,how_long;
  how_long=material_base.size();
  // 一価
  if(material_base.at(how_long-1)=='H' || material_base=="KOH"){
    valence=1;
    return valence;
  }
  // その他
  else{
    valence=(int)material_base.at(how_long-1)-48;
    return valence;
  }
}

// 前置されたイオンの文字列を返す
string ion_first(string material){
  string first="";
  // H_plus_ion
  if(material.at(0)=='H'){
    first="H";
    return first;
  }
  // KOH
  if(material=="KOH"){
    first+=material.at(0);
    return first;
  }
  // not CH3COOH
  else if(material!="CH3COOH"){
    first+=material.at(0);
    first+=material.at(1);
    return first;
  }
  // CH3COOH
  else{
    first="CH3COO";
    return first;
  }
}

// 後置されたイオンの文字列を返す
string ion_second(string material){
  string second="";
  // 酢酸の場合
  if(material=="CH3COOH"){
    second="H";
    return second;
  }
  // 酸の場合
  else if(material.at(0)=='H'){
    int check=valence_acid_fn(material);
    reverse(material.begin(),material.end());
    second=material;
    second.pop_back();
    // 1価でない
    if(check!=1){
      second.pop_back();
    }
    reverse(second.begin(),second.end());
    material=second;
    return material;
  }
  // 塩基の場合
  else{
    second="OH";
    return second;
  }
}

int main(){
  cout<<"中和反応系の問題を解くプログラム"<<endl;

 BEGIN: // 最初からを選択した場合
  string material_acid,material_base;
  printf("物質(酸性)の化学式を入力 (例:CH3COOH) : "); cin>>material_acid;
  printf("物質(塩基)の化学式を入力 (例:Ba(OH)2) : "); cin>>material_base;
  int valence_acid=valence_acid_fn(material_acid),valence_base=valence_base_fn(material_base);

 OTHER: // continue
  int continue_check;
  printf("計算問題→1 反応式→2 何価の何→3 終了→0 : ");
  int problem; cin>>problem;

  // 計算問題 mol/L or L
  if(problem==1){
    string ans;
    cout<<"1文字目は酸ならa 塩基ならb 2文字目は mol/Lならc Lならl"<<endl;
    cout<<"求めたいものを入力(例:ac) : "; cin>>ans;
    double ac,bc,al,bl,av,bv;
    av=valence_acid_fn(material_acid),bv=valence_base_fn(material_base);
    // mol/L
    if(ans.at(1)=='c'){
      // acid mol/L
      if(ans.at(0)=='a'){
        cout<<material_acid<<"のLを入力(例:1.0*10^-4なら0.0001) : "; cin>>al;
        cout<<material_base<<"のLを入力 : "; cin>>bl;
        cout<<material_base<<"のmol/Lを入力 : "; cin>>bc;
        ac=bc*bl*bv/al/av;
        cout<<material_acid<<"のmol/L = "<<ac<<endl;
      }
      // base mol/L
      else if(ans.at(0)=='b'){
        cout<<material_base<<"のLを入力(例:1.0*10^-4なら0.0001) : "; cin>>bl;
        cout<<material_acid<<"のLを入力 : "; cin>>al;
        cout<<material_acid<<"のmol/Lを入力 : "; cin>>ac;
        bc=ac*al*av/bl/bv;
        cout<<material_base<<"のmol/L = "<<bc<<endl;
      }
    }
      // L
    else if(ans.at(1)=='l'){
      // acid L
      if(ans.at(0)=='a'){
        cout<<material_acid<<"のmol/Lを入力(例:1.0*10^-4なら0.0001) : "; cin>>al;
        cout<<material_base<<"のLを入力 : "; cin>>bl;
        cout<<material_base<<"のmol/Lを入力 : "; cin>>bc;
        al=bc*bl*bv/ac/av;
        cout<<material_acid<<"のL = "<<al<<endl;
      }
      // base L
      else if(ans.at(0)=='b'){
        cout<<material_base<<"のmol/Lを入力(例:1.0*10^-4なら0.0001) : "; cin>>bl;
        cout<<material_acid<<"のLを入力 : "; cin>>al;
        cout<<material_acid<<"のmol/Lを入力 : "; cin>>ac;
        bl=ac*al*av/bc/bv;
        cout<<material_base<<"のL = "<<bl<<endl;
      }
    }

    cout<<"続ける→1 始めから→2 終了→0 : ";
    cin>>continue_check;
    if(continue_check==1){
      goto OTHER;
    }else if(continue_check==2){
      goto BEGIN;
    }else if(continue_check==0){
      cout<<"終了"<<endl;
      return 0;
    }else{
      goto OTHER;
    }
  }
  
  // 反応式
  else if(problem==2){
    string salt="";
    int c_acid,c_base, c_H2O;//coefficient 係数
    string c_acid_s,c_base_s,c_H2O_s;
    c_acid=valence_acid_fn(material_acid),c_base=valence_base_fn(material_base),c_H2O=c_acid*c_base;
    // 係数が一致
    if(c_acid==c_base){
      c_H2O=c_base,c_acid=1,c_base=1;
    }
    c_acid_s=to_string(c_acid);
    c_base_s=to_string(c_base);
    c_H2O_s=to_string(c_H2O);
    // 1は書かない
    if(c_acid==1){
      c_acid_s="";
    }
    if(c_base==1){
      c_base_s="";
    }
    if(c_H2O==1){
      c_H2O_s="";
    }
    // CH3COOH の場合
    if(material_acid=="CH3COOH"){
      // 相手の価数が1
      if(c_base==1){
        salt+=ion_first(material_acid)+ion_first(material_base);
      }
      // 相手の価数が一致しない
      else{
        salt+="("+ion_first(material_acid)+")"+to_string(c_base)+ion_first(material_base);
      }
    }
    // not CH3COOH
    else{
      // 価数が一致
      if(c_acid==c_base){
        salt+=ion_first(material_base) + ion_second(material_acid);
      }
      // 価数が一致しない
      else{
        salt+=ion_first(material_base)+c_acid_s;
        // 原子団
        if(valence_base_fn(material_base)!=1 && material_acid!="HCl"){
          salt+="(" + ion_second(material_acid) + ")";
          salt+=c_base_s;
        }
        // 原子
        else{
          salt+=ion_second(material_acid);
          salt+=c_base_s;
        }
      }
    }
    cout<<c_base_s<<material_acid<<" + "
        <<c_acid_s<<material_base<<" = "
        <<salt<<" + "
        <<c_H2O_s<<"H2O"<<endl;

    cout<<"続ける→1 始めから→2 終了→0 : ";
    cin>>continue_check;
    if(continue_check==1){
      goto OTHER;
    }else if(continue_check==2){
      goto BEGIN;
    }else if(continue_check==0){
      cout<<"終了"<<endl;
      return 0;
    }else{
      goto OTHER;
    }
  }
  
  // 何価の何
  else if(problem==3){
    // strong_acid
    if(material_acid=="HCl" || material_acid=="H2SO4" || material_acid=="HNO3"){
      cout<<material_acid<<"は"
          <<valence_acid<<"価の強酸"<<endl;
    }
    // weak_acid
    else{
      cout<<material_acid<<"は"
          <<valence_acid<<"価の弱酸"<<endl;
    }
    string base_judge="";
    int weak_strong;
    // KOH
    if(material_base.at(0)=='K'){
      base_judge+=material_base.at(0);
      weak_strong=1;
    }
    // not KOH
    else{
      base_judge+=material_base.at(0);
      base_judge+=material_base.at(1);
      // srtong_base
      if(base_judge=="Li" || base_judge=="Na" || base_judge=="Ca" || base_judge=="Sr" || base_judge=="Ba"){
        weak_strong=1;
      }
      // weak_base
      else{
        weak_strong=0;
      }
    }
    // cout st_b
    if(weak_strong==1){
      cout<<material_base<<"は"
          <<valence_base<<"価の強塩基"<<endl;
    }
    // cout we_b
    else{
      cout<<material_base<<"は"
          <<valence_base<<"価の弱塩基"<<endl;
    }

    cout<<"続ける→1 始めから→2 終了→0 : ";
    cin>>continue_check;
    if(continue_check==1){
      goto OTHER;
    }else if(continue_check==2){
      goto BEGIN;
    }else if(continue_check==0){
      cout<<"終了"<<endl;
      return 0;
    }else{
      goto OTHER;
    }
  }
  
  // 終了
  else if(problem==0){
    cout<<"終了"<<endl;
    return 0;
  }
  
  // 戻す
  else{
    goto OTHER;
  }
}
