#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Sensor {
    int sensor_id;
    float sicaklik;
};

int main() {
    long long Student_id;
    cout << "Enter your student ID: ";
    cin >> Student_id;
    
    int N = Student_id % 50;
    int E = Student_id % 100;
    fstream file("sensors.bin", ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "file couldn't be opened" << endl;
        return 1;
    }

    Sensor tempSensor;

    file.seekg(N * sizeof(Sensor), ios::beg);
    file.read(reinterpret_cast<char*>(&tempSensor), sizeof(Sensor)); 

    float firstTemperature = tempSensor.sicaklik;
    tempSensor.sicaklik += E; 

    file.seekp(N * sizeof(Sensor), ios::beg); 
    file.write(reinterpret_cast<char*>(&tempSensor), sizeof(Sensor));

    file.close();

    string dosyaAdi = to_string(Student_id) + "_Quiz5.txt";
    ofstream rapor(dosyaAdi);

    if (rapor.is_open()) {
        rapor << "Number: [" << Student_id << "]" << endl;
        rapor << "Sensor Index Used in the Process: [" << N << "]" << endl;
        rapor << "First Temperature: [" << firstTemperature  
              << "] -> New Temperature: [" << tempSensor.sicaklik << "]" << endl;
        
        rapor.close();
        cout << "done, rapor dosyasi: " << dosyaAdi << endl;
    }

    return 0;
}