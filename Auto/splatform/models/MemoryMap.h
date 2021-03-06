
#define CAN_DATA  0x0
#define CAN_IDENT 0x10
#define CAN_RTR   0x14
#define CAN_IDE   0x18
#define CAN_SIZE  0x1C

#define CAN_RXDATA  0x20
#define CAN_RXIDENT 0x30
#define CAN_RXRTR   0x34
#define CAN_RXIDE   0x38
#define CAN_RXSIZE  0x3C

#define CAN_ACK 0x40

#define BRAKEID 0x100
#define ACCELERATORID 0x200
#define SPEEDID 0x300
#define SPEEDIDFL 0x310
#define SPEEDIDFR 0x320
#define SPEEDIDBL 0x330
#define SPEEDIDBR 0x340
#define RPMID 0x400

#define WHEEL_FL 0
#define WHEEL_FR 1
#define WHEEL_BL 2
#define WHEEL_BR 3
