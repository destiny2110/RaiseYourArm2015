#include "hostcomm.h"

HostComm::HostComm(QObject *parent) : QObject(parent)
{
    head=0;
    tail=0;
    overflowFlag=false;
    newDataFlag=0;
    for (int i=0;i<1024;i++)
    {
        buffer[i]=0;
    }

}

HostComm::~HostComm()
{

}

// edit here
quint16 HostComm::prepareImgUpdate(quint8 *data, quint32 angle, quint32 angle_2, quint16 x, quint16 y, quint16 x_dest, quint16 y_dest)
{
    int index = 0;
    quint16 crc;
    data[index++]=0xA5;
    data[index++]=0;
    data[index++]=0;
    data[index++]=MSG_IMG_UPDATE;
    data[index++]=0;
    data[index++]=1;
    data[index++]=0;

    copyToArray(data+index,(quint8*)&angle,2);
    index+=2;
    copyToArray(data+index,(quint8*)&angle_2,2);
    index+=2;
    copyToArray(data+index,(quint8*)&x,2);
    index+=2;
    copyToArray(data+index,(quint8*)&y,2);
    index+=2;
    copyToArray(data+index,(quint8*)&x_dest,2);
    index+=2;
    copyToArray(data+index,(quint8*)&y_dest,2);
    index+=2;

    crc=calcCheckSum(data+3,index-3);
    data[1]=index-3;
    data[2]=(index-3)>>8;
    data[index++]=crc;
    data[index++]=crc>>8;

    data[index++]=0x0D;
    return index;
}

quint16 HostComm::startImgProc(quint8 *data, quint32 angle, quint16 x, quint16 y, quint16 x_dest, quint16 y_dest)
{
    int index = 0;
    quint16 crc;
    data[index++]=0xA5;
    data[index++]=0;
    data[index++]=0;
    data[index++]=MSG_START_TEST;
    data[index++]=0;
    data[index++]=1;
    data[index++]=0;
    copyToArray(data+index,(quint8*)&angle,4);
    index+=4;
    copyToArray(data+index,(quint8*)&x,2);
    index+=2;
    copyToArray(data+index,(quint8*)&y,2);
    index+=2;
    copyToArray(data+index,(quint8*)&x_dest,2);
    index+=2;
    copyToArray(data+index,(quint8*)&y_dest,2);
    index+=2;
    crc=calcCheckSum(data+3,index-3);
    data[1]=index-3;
    data[2]=(index-3)>>8;
    data[index++]=crc;
    data[index++]=crc>>8;
    data[index++]=0x0D;
    return index;
}








void HostComm::hostRecv(quint8 c)
{
    buffer[tail]=c;
    tail++;
    if (tail>=MAX_LENGTH)
    {
        tail=0;
    }
    if (tail==head) overflowFlag=true;
//    if ((tail+MAX_LENGTH)<(head+6) || (tail<(head+6)&&head<tail))
//        return;
    // Frame check
    for (int i=head;i!=tail;i=(i+1)%MAX_LENGTH)
    {
        if (buffer[i]==START_FRAME_CHAR)
        {
            len = buffer[i+1];
            len |= buffer[i+2]<<8;
            if (buffer[i+2+len+3]==END_FRAME_CHAR)
            {
                quint16 crc = buffer[i+len+3];
                crc |= buffer[i+len+4]<<8;
                if (calcCheckSum(&buffer[i+3],len)==crc)
                {
                    newDataFlag=true;
                    this->len = len;
                    frameStart = i+3;
                    frameEnd = i+2+len;
                    head=frameEnd+4;
                    emit recvData();
                    break;
                }
            }
        }
    }
}

quint16 HostComm::hostGet(quint8 *data)
{
    if (newDataFlag)
    {
        newDataFlag = false;
        for (int j=0;j<len;j++)
        {
            data[j]=buffer[frameStart+j];
        }
        return len;
    }
    else
    {
        return 0;
    }
}

quint16 HostComm::hostGetLength()
{
    return len;
}

quint16 HostComm::calcCheckSum(quint8 *data, quint8 len)
{
    quint16 sum=0;
    for (int i=0; i<len; i++)
    {
        sum+=data[i];
    }
    return sum;
}

quint16 HostComm::preparePID(quint8 *data,float kp, float ki, float kd)
{
    int index = 0;
    qint64 Kp,Ki,Kd;
    double temp=kp;
    quint16 crc;
    if (temp>20.0)
        temp=2.0;
    else if (temp<0.0)
        temp=0.0;
    Kp=static_cast<qint64>(temp*PID_PARAMS_SCALE);
    temp=ki;
    if (temp>20.0)
        temp=20.0;
    else if (temp<0.0)
        temp=0.0;
    Ki=static_cast<qint64>(temp*PID_PARAMS_SCALE);
    temp=kd;
    if (temp>20.0)
        temp=20.0;
    else if (temp<0.0)
        temp=0.0;
    Kd=static_cast<qint64>(temp*PID_PARAMS_SCALE);
    data[index++]=0xA5;
    data[index++]=0;
    data[index++]=0;
    data[index++]=MSG_SET_PID;
    data[index++]=0;
    data[index++]=1;
    data[index++]=0;
    data[index++]=Kp>>24;
    data[index++]=Kp>>16;
    data[index++]=Kp>>8;
    data[index++]=Kp;
    data[index++]=Ki>>24;
    data[index++]=Ki>>16;
    data[index++]=Ki>>8;
    data[index++]=Ki;
    data[index++]=Kd>>24;
    data[index++]=Kd>>16;
    data[index++]=Kd>>8;
    data[index++]=Kd;
    data[1]=index-3;
    data[2]=(index-3)>>8;
    crc=calcCheckSum(data+3,index-3);
    data[index++]=crc;
    data[index++]=crc>>8;
    data[index++]=0x0D;
    return index;
}

quint16 HostComm::prepareSpeedSet(quint8 *data, quint32 speedLeft, quint32 speedRight)
{
    int index = 0;
    quint16 crc;
    data[index++]=0xA5;
    data[index++]=0;
    data[index++]=0;
    data[index++]=MSG_SPEED_SET;
    data[index++]=0;
    data[index++]=1;
    data[index++]=0;
    copyToArray(data+index,(quint8*)&speedLeft,4);
    index+=4;
    copyToArray(data+index,(quint8*)&speedLeft,4);
    index+=4;
    crc=calcCheckSum(data+3,index-3);
    data[1]=index-3;
    data[2]=(index-3)>>8;
    data[index++]=crc;
    data[index++]=crc>>8;
    data[index++]=0x0D;
    return index;
}

void HostComm::getUpdate(quint8 *data, qint32 *vl, qint32 *vr, qint32 *left, qint32 *right,
               quint16 * ir1, quint16 *ir2, quint16 *ir3, quint16 *ir4)
{
    int index=4;
    copyFromArray(data+index,(quint8*)left,4);
    index+=4;
    copyFromArray(data+index,(quint8*)right,4);
    index+=4;
    copyFromArray(data+index,(quint8*)vl,4);
    index+=4;
    copyFromArray(data+index,(quint8*)vr,4);
    index+=4;
    copyFromArray(data+index,(quint8*)ir1,2);
    index+=2;
    copyFromArray(data+index,(quint8*)ir2,2);
    index+=2;
    copyFromArray(data+index,(quint8*)ir3,2);
    index+=2;
    copyFromArray(data+index,(quint8*)ir4,2);
    index+=2;
}

void HostComm::copyToArray(quint8 *data, quint8 *x, int len)
{
    for (int i=0;i<len;i++)
    {
        *data++ = *x++;
    }
}

void HostComm::copyFromArray(quint8 *data, quint8 *x, int len)
{
    for (int i=0;i<len;i++)
    {
        *x++ = *data++;
    }
}
