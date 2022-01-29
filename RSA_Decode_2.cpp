#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

//pass in the length of cipherMessage, and the cipher message's storage 
void Enter_cipherMessage(int m, vector<int>& ciphertext){
    int cipherMessage;
    
    for(int i = 0; i < m ; ++i)
    {
        cin >> cipherMessage;
        ciphertext.push_back(cipherMessage);
    }
}

//pass in the value of n, get the prime factor p and q, store in the array.
void calculate_P_Q(int n, vector<int>& p_q){

    for(int i = 2; i < n; ++i){
        if(n % i == 0){
            p_q.push_back(i);
        }
    }
}

//pass in e, and phi_n, check weather if the gcd(e, phi_n) is 1 or not.
int check_Key_Valid(int e, int phi_n){

    if(e == phi_n){
        return e;
    }


    if(e > phi_n){
        int temp = e;
        e = phi_n;
        phi_n = temp; 
    }

    return check_Key_Valid(e, phi_n - e);
}

//pass in e and phi_n to find d. Note: secret key = (d, n)
void compute_secretKey(int e, int phi_n, int& d){
    int x = 1;
    int y = 1;

    //Note d = e^-1 (mod phi_n) 
    while( (e * x) - 1 != (phi_n * y) ) {
        if( (e * x) < (phi_n * y)) {
            x++;
        }
        else
        {
            y++;
        }
    }

    d = x;
}

//use the secreate key to decode the message, store in the decoded Message vector
void Decode_Message(vector<int>& ciphertext, int d, int n, vector<int>& decoded_Message){

    //steps: for cipher test(M). decoded_Test =  (M^d) mod n;
    for(int i = 0; i < ciphertext.size(); ++i){
        int temp = ciphertext[i];
        int ans = 0; 

        //because start at 0, so end at d-1.
        for(int j = 0; j < (d-1); ++j){
            temp = temp * ciphertext[i];
            ans = temp % n; 
            temp = ans;
        }

        decoded_Message.push_back(ans);
    }

}

//print decoded message in int format.
void print_Decode_Message_int(vector<int>& decoded_Message){
    for(int i = 0; i < decoded_Message.size(); ++i){
        cout << decoded_Message[i] << " ";

        //format
        if(i + 1 % 15 == 0){
            cout << endl;
        }
    }

    cout << endl;
}

void print_Decode_Message_Text(const vector<int>& decoded_Message){
    char Decode_Table[31] = {
    'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' ,  'J' , 'K' , 'L' ,
    'M' , 'N' , 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' ,
    'Y' , 'Z' , ' ' , '\"', '.' , ',' , '\'' };

    for(int i = 0; i < decoded_Message.size(); ++i){
        //Example: A is 3 in decoded Message, and it's index 0 in the decode table, so -3 here.
        cout << Decode_Table[decoded_Message[i] - 3] << " ";
    }
}

int main(){
    //e, and n are the public key for RSA, m(the number of characters in the message)5
    int e, n, m;

    cin >> e >> n;
    cin >> m;

    vector<int> ciphertext;
    Enter_cipherMessage(m, ciphertext);

    //set the default of p and q to 0;
    vector<int>p_q;
    calculate_P_Q(n, p_q);

    int  phi_n= (p_q[0] - 1) * (p_q[1] - 1);
    //cout << "p = " << p_q[0] << ", q = " << p_q[1] << ", Phi_n = " << phi_n << ", e = " << e << endl;

    if(( p_q.size() != 2 || check_Key_Valid(e, phi_n) != 1)){
        cout << "Public key not valid!" << endl;
        exit(-1);
    }

    //d is the secret key.
    int d = -1; 
    compute_secretKey(e, phi_n, d);
    //cout << "Secret key: " << "(" << d << " , " << n << ")" << endl;

    
    cout << "HELLO" << endl;

    cout << p_q[0] << " " << p_q[1] << " " << phi_n << " " << d << endl;

    vector<int> decoded_Message;
    Decode_Message(ciphertext, d, n, decoded_Message);
    print_Decode_Message_int(decoded_Message);
    print_Decode_Message_Text(decoded_Message);

    return 0;
}