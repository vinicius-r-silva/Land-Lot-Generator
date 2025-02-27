#include <parking_spot_cpp/lib/vector.h>
#include <parking_spot_cpp/lib/globals.h>
#include <algorithm>
#include <set>

template <typename T>
void vector<T>::push_sorted(const T& r) {
    auto it = std::lower_bound(this->begin(), this->end(), r);
    this->insert(it, r);
}

// makes a reference copy of the elements
template <typename T>
void vector<T>::push_recursive(const vector<T>& v2) {
    this->insert(this->end(),
          std::make_move_iterator(v2.begin()),
          std::make_move_iterator(v2.end()));
    // this->insert(this->end(), v2.begin(), v2.end());
}

// need to be sorted
template <typename T>
void vector<T>::remove_duplicates() {
    this->erase(std::unique(this->begin(), this->end()), this->end());
}

// template <typename T>
// void vector<T>::remove_duplicates_unsorted() {
//   // std::set<T> s( this->begin(), this->end() );
//   // this->assign( s.begin(), s.end() );
//   std::vector<T> uniqueVec;

//   for (const auto& item : this) {
//       if (std::find(uniqueVec.begin(), uniqueVec.end(), item) == uniqueVec.end()) {
//           uniqueVec.push_back(item);
//       }
//   }

//   // this = std::move(uniqueVec);
// }


template <typename T>
void vector<T>::sort() {
    std::sort(this->begin(), this->end());
}