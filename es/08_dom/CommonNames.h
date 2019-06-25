#ifndef _COMMON_NAMES_H_
#define _COMMON_NAMES_H_

#include "Task.h"
#include <iostream>
#include <vector>
#include <set>

// Combine two overlapped vectors into one unique with sets usage
// Mathematic set COMPLEMENT operation


namespace aelzns {

class CommonNames : public Task {
  public:
    CommonNames() {}
    virtual ~CommonNames(){}

    static std::vector<std::string> findCommon(
                                            const std::vector<std::string>& names1,
                                            const std::vector<std::string>& names2) {
      std::set<std::string> out1;

      std::vector<std::string> out2;
      std::vector<std::string>::const_iterator it1;

      for (it1 = names1.begin();it1 != names1.end(); ++it1) {
        out1.insert(*it1);
      }

      for (auto it2 = names2.begin();it2 != names2.end();++it2)  {
        out1.insert(*it2);
      }

      for (auto it = out1.begin(); it != out1.end(); ++it) {
        std::cout<< "\tAELZ set scope: "<<*it<<std::endl;
        out2.push_back(*it);
      }
      return out2;
  }

  virtual bool execute() {
    std::cout<<"\t"<<__PRETTY_FUNCTION__<<"  COMPLEMENT algorithm started"<<std::endl;

    std::vector<std::string> names1 = {"Ava", "Emma", "Olivia"};
    std::vector<std::string> names2 = {"Olivia", "Sophia", "Emma"};

    std::vector<std::string> result = CommonNames::findCommon(names1, names2);
    for(auto element : result)  {
      std::cout <<"\t"<< element << ' '; // should print Ava Emma Olivia Sophia
    }
    std::cout << std::endl<<std::endl;
    return 0;
  }

};
}
#endif
