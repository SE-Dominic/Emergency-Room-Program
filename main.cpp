#include <iostream>
#include <queue> //for priority queue (heap)
#include <unordered_map> //for map
#include <limits>
#include <typeinfo> //for typeid
using namespace std;

//user should be able to add new patient to line
//remove user who gets seen
//view patient info

class patient {
private:
    string fname, lname;
    unsigned severity; //1 (most severe) - 5 (least severity)
    string diagnosis;
public:
    patient() { fname = lname = diagnosis = " ", severity = 5; }
    patient(string f, string l, unsigned s, string d) {
        fname = f;
        lname = l;
        severity = s;
        diagnosis = d;
    }
    
    //getters
    string get_first_name() const {
        return this->fname;
    }
    string get_last_name() const {
        return this->lname;
    }
    unsigned get_severity() const {
        return this->severity;
    }
    string get_Description() const {
        return this->diagnosis;
    }
}; //end patient class

void menu() {
    cout << endl;
    cout << "1. ADD PATIENT TO LINE" << endl;
    cout << "2. SEE NEXT PATIENT" << endl;
    cout << "3. VIEW PATIENT INFO" << endl;
    cout << "4. EXIT" << endl;
    cout << endl;
}
/*
You need to create this struct because a priority queue by default 
is a max heap so its greatest -> smallest. This structure ensures that 
the larger severity will go to the end of the queue while the smaller 
severity will remain at the front.
*/
struct ComparePatients {
    bool operator()(const patient& a, const patient& b) const {
        return a.get_severity() > b.get_severity();
    }
};

int main() {
    priority_queue<patient, vector<patient>, ComparePatients> line; //creates a min heap
    unordered_map<string, patient> map; //last name, patient
    menu();
    int choice;
    cout << "Option: " << endl;
    cin >> choice;
    while (choice != 4) {
        if (choice == 1) {
            string fn, ln, des;
            unsigned sev;
            cout << "First Name: ";
            cin >> fn;
            cout << "Last Name: ";
            cin >> ln;
            cout << "Severity: "; //taken severity input
            cin >> sev;
            /*
                - check if its correct type
                - check if input is within given range
                    - output error messages
                    - at the end of all this give input again
            */
            if (typeid(sev) != typeid(unsigned) || sev < 1 || sev > 5) {
                cout << "Error! Severity must be a number (integer) between 1 and 5.\n";
                if (sev < 1 || sev > 5) {
                    cout << "Error! Severity must be between 1 and 5. \n";
                }
                cout << "Severity: ";
                cin >> sev;
            }
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // throw away everything till the new line
            cout << "Description: ";
            getline(cin, des);
            patient data = patient(fn, ln, sev, des);
            line.push(data);
            string key = fn + "_" + ln;
            map.emplace(key, data);
            cout << "\033[2J\033[1;1H";
            // \033[2j clears screen
            //\033[1;1H" moves cursor to top left
        } else if (choice == 2) {
            if (!line.empty()) {
                patient next = line.top();
                string key = next.get_first_name() + "_" + next.get_last_name();
                cout << endl << "Next in line: " << endl;
                cout << next.get_last_name() << ", " << next.get_first_name() << endl;
                cout << "Severity: " << next.get_severity() << endl;
                cout << "Diagnosis: " << next.get_Description() << endl;
                line.pop();
                map.erase(key);
            } else {
                cout << "No patient's in line. " << endl;
            }
        } else if (choice == 3) {
            //put data into map
            string f, l;
            cout << "Enter patient's first name: ";
            cin >> f;
            cout << "Enter patient's last name: ";
            cin >> l;
            string key = f + "_" + l;
            unordered_map<string, patient>::const_iterator it = map.find(key);
            if (it != map.end()) {
                cout << "Name was found with -> " << it->second.get_last_name() << ", " << it->second.get_first_name() <<  endl;
                cout << "Severity: " << it->second.get_severity() << endl;
                cout << "Description: " << it->second.get_Description() << endl;
            } else {
                cout << "Key not found." << endl;
            }
        } else {
            cout << "Invalid choice. Try again\n";
            cout << "Option: ";
            cin >> choice;
        }
        
        menu();
        cout << "Option: ";
        cin >> choice;
    }
    if (choice == 4) {
        if (line.empty()) {
            cout << "Line is empty. Closing program " << endl;
            return 0;
        }
        cout << "finishing reset of line..." << endl;
        while(!line.empty()) {
            patient next_patient = line.top();
            cout << "Seeing next patient: " << " (" << next_patient.get_severity() << ") " <<  next_patient.get_last_name() << ", " << next_patient.get_first_name() << endl;
            line.pop(); //clear rest of line
        }
            map.clear(); //clears map
    }
    return 0;
}
