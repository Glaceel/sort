#include <iostream>
#include <ctime>
using namespace std;

struct Team {
    string name;
    int titles;
};

void generate_teams_manual(Team teams[], int n) {
    if (n != 300) {
        cout << "Error: Expected 300 teams." << endl;
        return;
    }
    for (int i = 0; i < 300; ++i) {
        teams[i] = {"Team-" + to_string(i + 1), rand() % 18 + 1};
    }
}

void quick_sort_iterative(Team arr[], int n) {
    int stack[300][2], top = -1;
    stack[++top][0] = 0;
    stack[top][1] = n - 1;

    while (top >= 0) {
        int low = stack[top][0], high = stack[top--][1];
        if (low < high) {
            int pivot = arr[high].titles, i = low - 1;
            for (int j = low; j < high; ++j) {
                if (arr[j].titles >= pivot) swap(arr[++i], arr[j]);
            }
            swap(arr[i + 1], arr[high]);
            stack[++top][0] = low; stack[top][1] = i;
            stack[++top][0] = i + 2; stack[top][1] = high;
        }
    }
}

void merge_sort_recursive(Team arr[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_recursive(arr, left, mid);
    merge_sort_recursive(arr, mid + 1, right);
    Team temp[300];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) temp[k++] = arr[i].titles >= arr[j].titles ? arr[i++] : arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int p = 0; p < k; ++p) arr[left + p] = temp[p];
}

int main() {

    srand(time(0));
    Team teams[300], teams_quick_sort[300], teams_merge_sort[300];
    generate_teams_manual(teams, 300);

    for (int i = 0; i < 300; ++i) teams_quick_sort[i] = teams_merge_sort[i] = teams[i];

    clock_t start = clock();
    quick_sort_iterative(teams_quick_sort, 300);
    double quick_sort_time = double(clock() - start) / CLOCKS_PER_SEC;

    start = clock();
    merge_sort_recursive(teams_merge_sort, 0, 299);
    double merge_sort_time = double(clock() - start) / CLOCKS_PER_SEC;

    cout << "(Quick Sort):\n";
    for (int i = 0; i < 300; ++i) cout << teams_quick_sort[i].name << " (" << teams_quick_sort[i].titles << ")\n";

    cout << "\n(Merge Sort):\n";
    for (int i = 0; i < 300; ++i) cout << teams_merge_sort[i].name << " (" << teams_merge_sort[i].titles << ")\n";

    cout << "\nQuick Sort Time: " << quick_sort_time << " seconds\n";
    cout << "Merge Sort Time: " << merge_sort_time << " seconds\n";

    return 0;
}
