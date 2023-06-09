#pragma once
#include "Object.h"
#include"game.h"
class SpringBase :
    public Object
{
public:
    SpringBase(VECTOR _pos,VECTOR _vec,float _length,float _size,float _roll,float _pitch,float _yaw);
    virtual ~SpringBase();
    void Draw();
    void Update(float deltaTime);
    void SetRoll(float _roll);
    void SetPitch(float _pitch);
    void SetYaw(float _yaw);
    void SetRotate(float _roll, float _pitch, float _yaw);
    void SetPos(VECTOR _pos);

protected:
    VECTOR vec;//S²ÌxNg
    VECTOR normedVec;//³K»µ½vec
    float length;//·³
    float size;//~Ìå«³
    float roll;
    float pitch;
    float yaw;
    MATRIX matX;//X²ñ]sñ
    MATRIX matY;//Y²ñ]sñ
    MATRIX matZ;//Z²ñ]sñ
    unsigned int color;

    //ÅãÉÁ¦éñ]ÖA
    MATRIX rolled;
    MATRIX pitched;
    MATRIX yawed;
    VECTOR veced;
};

