//
// Created by Oleg Kuzenko on 02.08.2020.
//

#ifndef NODE_H
#define NODE_H

#include "Operations.h"
#include "ShuntingYardUtils.h"

namespace shunting_yard {
    namespace calculator {

        class NodeEvaluator {
        public:
            virtual double evaluate(double x = 0, double y = 0) = 0;
        };

        class Node : public NodeEvaluator {
        public:
            Node(std::string name, bool isFunction) : m_name(name), m_isFunction(isFunction) {}

            bool isFunction() const { return m_isFunction; }

            void setLeftNode(const std::shared_ptr<Node>& leftNode) { m_left = std::move(leftNode); }
            void setRightNode(const std::shared_ptr<Node>& rightNode) { m_right = std::move(rightNode); }

            std::shared_ptr<Node>& getLeftNode() { return m_left; }
            std::shared_ptr<Node>& getRightNode() { return m_right; }

        protected:
            std::string m_name;
            bool m_isFunction;

            std::shared_ptr<Node> m_right;
            std::shared_ptr<Node> m_left;
        };

        class FuncNode : public Node {
        public:
            FuncNode(std::string name)
                    : Node(name, true) {}

            void setUnary(bool isUnary) {
                this->isUnary = isUnary;

                this->func = isUnary ? shunting_yard::calculator::unary_functions[m_name] : shunting_yard::calculator::binary_functions[m_name];
            }

            double evaluate(double x, double y = 0) override {
                return this->func.eval(x, y);
            }

            bool isUnary;
            shunting_yard::calculator::Func func;
        };

        class NumNode : public Node {
        public:
            NumNode(std::string name) : Node(name, false) {}

            double evaluate(double x = 0, double y = 0) override {
                return shunting_yard::utils::getNumericalVal(m_name.c_str());
            }
        };
    }
}

#endif //NODE_H
