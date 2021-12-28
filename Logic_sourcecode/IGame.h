#ifndef IGAME_H
#define IGAME_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class IGame
{
    public:
        //Quang xuc xac
        virtual void rollDice() = 0;

        //Lay gia tri xuc xac cua nguoi choi vua thuc hien gan day nhat
        virtual int getDice() = 0;

        //Chuyen tien tu nguoi choi co idPlayerFrom toi nguoi choi co idPlayerTo voi gia tri tien chuyen la amnt
        //Id cua ngan hang quy uoc la so 0
        virtual void transferMoney(int idPlayerFrom, int idPlayerTo, int amnt) = 0;

        /*
            Yeu cau hien noi dung chua thong bao (va cac lua chon neu co) de nguoi choi biet va lua chon
                *text: noi dung thong bao hien thi
                *listQuery: danh sach cac lua chong duoi dang chuoi
                *waitResponde: thong bao nay co yeu cau nguoi dung thao tac de dong thong bao hay khong;
                    *true: nguoi dung can bam vao nut trong hop thoai de dong thong bao
                    *false: chi hien thi thong bao trong vai giay, dung de thong bao trang thai cua tro choi vua thay doi
        */
        virtual string notify(const string &text, const vector <string> &listQuery = {}, const bool waitResponde = false) = 0;
        
        //Di chuyen nguoi choi co idPlayer mot so luong pos buoc
        virtual void movePlayer(int idPlayer, int pos) = 0;
        
};

#endif