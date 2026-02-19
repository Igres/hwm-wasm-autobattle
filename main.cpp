#include <vector>
#include <emscripten/bind.h>

using namespace emscripten;

struct Unit {
    int x;
    int y;
};

static std::vector<Unit> g_units;

/*
    Получаем данные из JS
*/
void setUnits(const std::vector<Unit>& units) {
    g_units = units;
}

/*
    Пример тяжёлой логики
*/
int calculateSomething() {

    int sum = 0;

    for (const auto& u : g_units) {
        sum += u.x * u.y; // просто пример
    }

    return sum;
}

std::vector<Unit> getUnits() {
    return g_units;
}

EMSCRIPTEN_BINDINGS(my_module) {

    value_object<Unit>("Unit")
        .field("x", &Unit::x)
        .field("y", &Unit::y);

    register_vector<Unit>("VectorUnit");

    function("setUnits", &setUnits);
    function("calculateSomething", &calculateSomething);
    function("getUnits", &getUnits);
}
