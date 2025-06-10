#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <limits>

using namespace std;

struct Node {
    int flow;
    int valveId;
    vector<int> neighbours;
};

int valveIdCounter = 0;

vector<Node> valves(57);
int openValves = 0;
int maxFlow = 0;

map<long long, int> history;

bool valveOpen(int id) {
    return (1<<id) & openValves;
}
void openValve(int id) {
    openValves = openValves | (1 << id);
}
void closeValve(int id) {
    openValves &= ~(1 << id);
}

int hsize = 0;
void calculate(int vId, int flowSum, int totalFlow, int remainingTime) {
    if (totalFlow+flowSum*remainingTime > maxFlow) {
        cout << totalFlow+flowSum*remainingTime << endl;
    }
    maxFlow = max(maxFlow, totalFlow+flowSum*remainingTime);
    if (remainingTime <= 1)
        return;

    if (history[vId*30*65536ll+(remainingTime-1)*65536+openValves]>=totalFlow)
        return;
    else
        history[vId*30*65536ll+(remainingTime-1)*65536+openValves] = totalFlow;

    auto &v1 = valves[vId];
    if (v1.flow && !valveOpen(v1.valveId)) {
        openValve(v1.valveId);
        int fsum = flowSum+v1.flow;
        calculate(vId, fsum, totalFlow+flowSum, remainingTime-1);
        closeValve(v1.valveId);
    }

    for (auto nId1 : v1.neighbours) {
        calculate(nId1, flowSum, totalFlow+flowSum, remainingTime-1);
    }
}

int main()
{
    map<string, int> nameToId{{"AA", 1}};

    stringstream ss("Valve JI has flow rate=21; tunnels lead to valves WI, XG\nValve DM has flow rate=3; tunnels lead to valves JX, NG, AW, BY, PF\nValve AZ has flow rate=0; tunnels lead to valves FJ, VC\nValve YQ has flow rate=0; tunnels lead to valves TE, OP\nValve WI has flow rate=0; tunnels lead to valves JI, VC\nValve NE has flow rate=0; tunnels lead to valves ZK, AA\nValve FM has flow rate=0; tunnels lead to valves LC, DU\nValve QI has flow rate=0; tunnels lead to valves TE, JW\nValve OY has flow rate=0; tunnels lead to valves XS, VF\nValve XS has flow rate=18; tunnels lead to valves RR, OY, SV, NQ\nValve NU has flow rate=0; tunnels lead to valves IZ, BD\nValve JX has flow rate=0; tunnels lead to valves DM, ZK\nValve WT has flow rate=23; tunnels lead to valves OV, QJ\nValve KM has flow rate=0; tunnels lead to valves TE, OL\nValve NG has flow rate=0; tunnels lead to valves II, DM\nValve FJ has flow rate=0; tunnels lead to valves AZ, II\nValve QR has flow rate=0; tunnels lead to valves ZK, KI\nValve KI has flow rate=9; tunnels lead to valves ZZ, DI, TL, AJ, QR\nValve ON has flow rate=0; tunnels lead to valves LC, QT\nValve AW has flow rate=0; tunnels lead to valves DM, AA\nValve HI has flow rate=0; tunnels lead to valves TE, VC\nValve XG has flow rate=0; tunnels lead to valves II, JI\nValve II has flow rate=19; tunnels lead to valves LF, NG, OL, FJ, XG\nValve VC has flow rate=24; tunnels lead to valves WI, HI, AZ\nValve VJ has flow rate=0; tunnels lead to valves UG, AA\nValve IZ has flow rate=0; tunnels lead to valves VF, NU\nValve EJ has flow rate=0; tunnels lead to valves ZK, LC\nValve DU has flow rate=12; tunnels lead to valves TC, UG, FM\nValve ZK has flow rate=10; tunnels lead to valves JX, EJ, JW, QR, NE\nValve XF has flow rate=25; tunnels lead to valves OP, VT\nValve LC has flow rate=4; tunnels lead to valves FM, EJ, ON, AJ, PF\nValve SV has flow rate=0; tunnels lead to valves XS, IY\nValve LF has flow rate=0; tunnels lead to valves II, OV\nValve DI has flow rate=0; tunnels lead to valves KI, BY\nValve OP has flow rate=0; tunnels lead to valves YQ, XF\nValve NQ has flow rate=0; tunnels lead to valves TC, XS\nValve QJ has flow rate=0; tunnels lead to valves VT, WT\nValve IY has flow rate=22; tunnel leads to valve SV\nValve AJ has flow rate=0; tunnels lead to valves LC, KI\nValve TE has flow rate=11; tunnels lead to valves QI, HI, KM, YQ\nValve ZZ has flow rate=0; tunnels lead to valves KI, AA\nValve VT has flow rate=0; tunnels lead to valves XF, QJ\nValve OL has flow rate=0; tunnels lead to valves KM, II\nValve TC has flow rate=0; tunnels lead to valves NQ, DU\nValve TL has flow rate=0; tunnels lead to valves VF, KI\nValve QT has flow rate=0; tunnels lead to valves AA, ON\nValve BY has flow rate=0; tunnels lead to valves DM, DI\nValve OV has flow rate=0; tunnels lead to valves LF, WT\nValve VN has flow rate=0; tunnels lead to valves RR, BD\nValve VF has flow rate=13; tunnels lead to valves OY, IZ, TL\nValve BD has flow rate=17; tunnels lead to valves NU, VN\nValve UG has flow rate=0; tunnels lead to valves VJ, DU\nValve PF has flow rate=0; tunnels lead to valves LC, DM\nValve RR has flow rate=0; tunnels lead to valves XS, VN\nValve AA has flow rate=0; tunnels lead to valves QT, ZZ, AW, VJ, NE\nValve JW has flow rate=0; tunnels lead to valves ZK, QI");
    string line;
    while (getline(ss, line)) {
        line.erase(0, string("Valve ").size());
        string name = line.substr(0,2);
        line.erase(0, string("AA has flow rate=").size());
        size_t p;
        int flow = stoi(line, &p);
        int &id = nameToId[name];
        if (id==0) id=nameToId.size();
        auto &valve = valves[id];
        valve.flow = flow;
        if (flow>0) {
            valve.valveId=valveIdCounter++;
        }

        line.erase(0, p+string("; tunnels lead to valve ").size());
        if (line[0] == ' ') line.erase(0,1);
        while (!line.empty()) {
            string neighbour = line.substr(0,2);
            line.erase(0,4);

            int &nId = nameToId[neighbour];
            if (nId==0) nId=nameToId.size();
            valve.neighbours.push_back(nId);
        }
    }

    int t = 30;
    calculate(1, 0, 1, t);
    cout << maxFlow-1 << endl;
    cout << history.size() << endl;

}
