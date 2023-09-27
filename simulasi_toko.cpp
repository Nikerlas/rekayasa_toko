#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>

using namespace std;

class item
{
    private:
    int code;
    char name[15];
    int qty;

    public:
    void put_item(void);
    void get_item(void);
    int get_code(void)
    {
        return code;
    };
    

int update_qty(int num)
{
    qty = qty-num;
    return qty;
}

void inputCode()
{
    while (!(cin >> code))
    {
        cout<<"ERROR: a number must be entered: ";
        cin.clear();
        cin.ignore(132, '\n');
    }
}
};

void item::get_item(void)
{
    cout<<"Masukkan kode item: ";
    inputCode();
    //fflush(stdin);
    cout<<"Masukkan nama item: "; cin >> name;
    cout<<"Masukkan qty: "; cin >> qty;
}

void item::put_item(void)
{
    cout<<setw(6)<<code<<setw(15)<<name<<setw(6)<<qty<<endl;
}

void addRecord(void);
void showAll(void);
void showRecord(void);
void deleteRecord(void);
void modifRecord(void);

item it;
fstream file;

int main()
{
    int option;
    while(1)
    {
        system("cls");
        cout<<"===MENU==="<<endl;
        cout<<"1. Tambah record baru"<<endl;
        cout<<"2. Tampil semua data"<<endl;
        cout<<"3. Cari record tertentu"<<endl;
        cout<<"4. Hapus record"<<endl;
        cout<<"5. Ubah record"<<endl;
        cout<<"6. Keluar"<<endl;
        cout<<"Masukkan nomor opsi: "; cin>>option;
        switch(option)
        {
            case 1:
            {
                addRecord();
                cout<<"Tekan untuk kembali ke menu ...";
                getch();
                break;
            }
            case 2:
            {
                cout<<"-------------------------------\n";
                cout<<setw(6)<<"Kode"<<setw(15)<<"Nama"<<setw(6)<<"Qty"<<endl;
                cout<<"-------------------------------\n";
                showAll();
                cout<<"-------------------------------\n";
                cout<<"Tekan untuk kembali ke menu ...";
                getch();
                break;
            } 
            case 3: 
            {
                showRecord();
                cout<<"Tekan untuk kembali ke menu ...";
                getch();
                break;
            }
            case 4:
            {
                deleteRecord();
                cout<<"Tekan untuk kembali ke menu ...";
                getch();
                break;
            }
            case 5:
            {
                modifRecord();
                cout<<"Tekan untuk kembali ke menu ...";
                getch();
                break;
            }
            case 6:
            {
                exit(0);
            }
            default:
            {
                cout<<"Opsi pilihan tidak ada, tekan apa saja untuk kembali ke menu ...";
                getch();
                break;
            }
        }
    }
    return 0;
}

void addRecord()
{
    char ch = 'y';
    file.open("stock.dat", ios::app|ios::binary);
    while(ch == 'y' || ch =='Y')
    {
        it.get_item();
        file.write((char*)&it, sizeof(it));
        cout<<"Tambah record lagi ... (y/n)?";
        cin>>ch;
    }
    file.close();
}

void showAll()
{
    file.open("stock.dat", ios::in|ios::binary);
    if(!file)
    {
        cout<<"File not Found";
        exit(0);
    }
    else
    {
        file.read((char*)&it, sizeof(it));
        while (!file.eof())
        {
            it.put_item();
            file.read((char*)&it, sizeof(it));
        }
    }
    file.close();
}

void showRecord(void)
{
    int no, flag = 0;
    file.open("stock.dat", ios::in|ios::binary);
    if(!file)
    {
        cout<<"file tidak ditemukan";
        exit(0);
    }
    else
    {
        cout<<"Masukkan code yang dicari: ";
        cin>>no;
        while(!file.eof())
        {
            if(no==it.get_code())
            {
                flag=1;
                cout<<"------------------------------------------\n";
                cout<<setw(6)<<"Kode"<<setw(15)<<"Nama"<<setw(6)<<"Qty"<<endl;
                cout<<"------------------------------------------\n";
                it.put_item();
                cout<<"------------------------------------------\n";
                break;
            }
            file.read((char*)&it, sizeof(it));
        }
    }
    file.close();
}

void deleteRecord(void)
{
    int no;
    cout<<"Masukkan kode item untuk dihapus: ";
    cin>>no;
    ofstream file2;
    file2.open("new.dat", ios::binary);
    file.open("stock.dat",ios::in|ios::binary);
    if(!file)
    {
        cout<<"file not found";
        exit(0);
    }
    else
    {
        file.read((char*)&it, sizeof(it));
        while(!file.eof())
        {
            if(no != it.get_code())
            {
                file2.write((char*)&it, sizeof(it));
            }
            file.read((char*)&it, sizeof(it));
        }
    }
    file2.close();
    file.close();
    remove("stock.dat");
    rename("new.dat", "stock.dat");
}

void modifRecord(void)
{
    int no,num;
    cout<<"Masukkan kode item untuk dirubah: "; cin>>no;
    cout<<"Masukkan jumlah item yang akan di keluarkan: "; cin>>num;
    file.open("stock.dat", ios::in|ios::out|ios::binary);
    if(!file)
    {
        cout<<"File not found;";
        exit(0);
    }
    while(file.read((char*)&it, sizeof(it)))
    {
        if(it.get_code()==no)
        {
            it.update_qty(num);
            int pos = sizeof(it);
            file.seekp(-pos, ios::cur);
            file.write((char*)&it, sizeof(it));
        }
    }
    file.close();
}