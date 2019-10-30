#ifndef HOSTCOMM_H
#define HOSTCOMM_H

#include <QObject>
#define START_FRAME_CHAR 0xA5
#define END_FRAME_CHAR 0x0D
#define MAX_LENGTH 32768
#define MIN_LENGTH 6
#define PID_PARAMS_SCALE 100000000
enum MSG_CODE
{
    MSG_UPDATE_POS=0,
    MSG_TIME,
    MSG_BOX,
    MSG_WAYPOINT,
    MSG_TRACK_BOT,
    MSG_UPDATE_BOT,
    MSG_SPEED_SET,
    MSG_START_TEST,
    MSG_SET_PID,
    // edit here
    MSG_IMG_UPDATE,
};

// Frame
//---------------------------------------------------------------------------------------
// | Start byte | Length | Msg code | Source ID | Dest ID | Pack num |Payload | CRC    | End byte |
//---------------------------------------------------------------------------------------
// | 0xA5       | 2 byte | 1 byte   | 1 byte    | 1 byte  | 1 byte   |        | 2 byte | 0x0D     |
//---------------------------------------------------------------------------------------
// UPDATE POS: | x 4 float | y 4 float | theta 4 float | time 4 int |
// UPDATE BOT: | left 4 int | right 4 int | vl 4 int | vr 4 int | ir1 2 int | ir2 2 int | ir3 2 int | ir4 2 int|
// SPEED SET:  | vl 4 int | vr 4 int |

class HostComm : public QObject
{
    Q_OBJECT
public:
    explicit HostComm(QObject *parent = 0);
    ~HostComm();
    bool newDataFlag;
    bool overflowFlag;
    void hostRecv(quint8 c);
    quint16 hostGet(quint8 *data);
    quint16 hostGetLength();
    quint16 calcCheckSum(quint8 *data, quint8 len);
    quint16 prepareSpeedSet(quint8 *data, quint32 speedLeft, quint32 speedRight);
    quint16 preparePID(quint8 *data,float kp, float ki, float kd);
    quint16 prepareImgUpdate(quint8 *data, quint32 angle, quint32 angle_2, quint16 x, quint16 y, quint16 x_dest, quint16 y_dest);
    quint16 startImgProc(quint8 *data, quint32 angle, quint16 x, quint16 y, quint16 x_dest, quint16 y_dest);


    void getUpdate(quint8 *data, qint32 *vl, qint32 *vr, qint32 *left, qint32 *right,
                   quint16 * ir1, quint16 *ir2, quint16 *ir3, quint16 *ir4);
    void copyToArray(quint8 *data, quint8 *x, int len);
    void copyFromArray(quint8 *data, quint8 *x, int len);
    quint16 head,tail;
signals:
    void recvData();
public slots:

private:
    quint8 buffer[MAX_LENGTH];
    quint16 frameStart,frameEnd;
    int len;

};

#endif // HOSTCOMM_H
