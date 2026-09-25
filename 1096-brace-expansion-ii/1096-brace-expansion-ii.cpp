class Solution {
public:
    string s;
    int pos;

    // Parse a sequence of expressions until ',' or '}'
    set<string> parseSequence() {
        set<string> result;
        result.insert("");

        while (pos < s.size() &&
               s[pos] != ',' &&
               s[pos] != '}') {

            set<string> part = parseElement();

            set<string> temp;

            for (string a : result) {
                for (string b : part) {
                    temp.insert(a + b);
                }
            }

            result = temp;
        }

        return result;
    }

    // Parse one element: either a letter or {...}
    set<string> parseElement() {

        // Single letter
        if (s[pos] != '{') {
            set<string> result;
            result.insert(string(1, s[pos]));
            pos++;
            return result;
        }

        // Expression inside {...}
        pos++; // skip '{'

        set<string> result;

        while (true) {

            set<string> part = parseSequence();

            // Union
            result.insert(part.begin(), part.end());

            if (s[pos] == ',') {
                pos++;
            }
            else {
                break;
            }
        }

        pos++; // skip '}'

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        set<string> result = parseSequence();

        return vector<string>(result.begin(), result.end());
    }
};