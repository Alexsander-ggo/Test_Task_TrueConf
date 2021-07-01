#pragma once

#include <iostream>
#include <iterator>
#include <utility>

namespace ch {

    template <typename Container>
    class ContainerHolder {
    public:
        ContainerHolder() = default;

        explicit ContainerHolder(const Container& cont)
            : cont_(cont) {}

        template <typename Add>
        void Add(size_t cnt_el, Add add) {
            for (size_t i = 0; i < cnt_el; ++i) {
                add(cont_, i);
            }
        }

        template <typename Erase>
        void Erase(size_t cnt_el, Erase erase) {
            if (cont_.size() < cnt_el) {
                cont_.clear();
                return;
            }
            for (size_t i = 0; i < cnt_el; ++i) {
                erase(cont_);
            }
        }

        template <typename It, typename Comp, typename Add>
        void Syncing(It begin, It end, Comp comp, Add add) {
            Container tmp;
            for (auto it = cont_.begin(); it != cont_.end(); std::advance(it, 1)) {
                if (comp(begin, end, it)) {
                    add(tmp, it);
                }
            }
            cont_ = std::move(tmp);
        }

        auto Begin() {
            return cont_.begin();
        }

        auto End() {
            return cont_.end();
        }

        auto Begin() const {
            return const_cast<ContainerHolder>(*this).Begin();
        }

        auto End() const {
            return const_cast<ContainerHolder>(*this).End();
        }

        void Print(std::ostream& out = std::cout) const {
            out << cont_.size() << '\n';
            for (const auto& el : cont_) {
                out << el << '\t';
            }
            out << std::endl;
        }

    private:
        Container cont_;
    };
}