
typedef struct message {
    unsigned int ID;
    char length;
    char data[8];
} Message;


void CAN_LoopBack_Init();

void CAN_Message_Send(Message *message);

void CAN_Transmit_Complete();

void CAN_Data_Receive();

void CAN_Int_Vect();
