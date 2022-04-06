#include<bits/stdc++.h>
using namespace std;

struct dictionary{
    string word;
    int cnt;
    set<int> line_number;
};

vector<string> list_have_no_sense;
vector<dictionary> dic_list;

bool isCharacter(char c){
    if((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A')) return true;
    return false;
}


bool isName(string word){
    return (isupper(word[0]));
}

bool isNumber(string word){
    return (isdigit(word[0]));
}

bool wordNoSense(string word){
    for(std::vector<string>::iterator it = list_have_no_sense.begin() ; it != list_have_no_sense.end(); ++it){
        if(*it== word) return true;
    }
    return false;
}
vector<string> split_text(string text){
    vector<string> all_word_in_line;
    string new_word;

    for(int i=0; i<text.length(); i++){
        if(isCharacter(text[i])){
            new_word += text[i];
        }
        else{
            if(new_word.length() > 0){
                all_word_in_line.push_back(new_word);
                new_word = "";
            }
        }
    }
    if(new_word.length() > 0)  
    {
        all_word_in_line.push_back(new_word); 
    }
    return all_word_in_line;    
}

bool compareString(dictionary a, dictionary b)
{
    return a.word < b.word;
}

int main(){

    string text_line;

    ifstream file("stopw.txt");
    ifstream content("alice30.txt");

    while (getline(file, text_line))
    {
        list_have_no_sense.push_back(text_line);
    }
    file.close();

    int line_index = 1;

    while(getline(content, text_line)){
        vector<string> word_in_line = split_text(text_line);

        int position = 0;
        for(int i = 0; i < word_in_line.size(); i++){
            int check = 0;

            string word = word_in_line[i];
            if(position == 0) transform(word.begin(), word.end(), word.begin(), ::tolower);
            if(isName(word) || isNumber(word)|| wordNoSense(word)){
                ++position;
                continue;
            }

            for(std::vector<dictionary>::iterator it = dic_list.begin() ; it != dic_list.end(); ++it){
                if(it->word == word){
                    check = 1;
                    it->line_number.insert(line_index);
                    it->cnt++;
                    break;
                }
            }
            if(!check){
                dictionary temp2;
                temp2.word = word;
                temp2.cnt = 1;
                temp2.line_number.insert(line_index);
                dic_list.push_back(temp2);
            }
            position++;
        }
        line_index++;
    }

    sort(dic_list.begin(), dic_list.end(), compareString);
    for(std::vector<dictionary>::iterator it = dic_list.begin() ; it != dic_list.end(); ++it){
        cout << it->word << " " << it->cnt;
        for(std::set<int>::iterator y = it->line_number.begin() ; y != it->line_number.end(); ++y)
            cout << "," << *y;
        cout << endl;
    }
    content.close();
}