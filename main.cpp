#include <iostream>
#include <string>
#include <emscripten.h>

int happiness = 50, fullness = 50, cleanliness = 50, health = 100; 
std::string cat_name = "Cat"; 

extern "C" {
    
    EMSCRIPTEN_KEEPALIVE
    void update_status() {
        std::string message = "Я " + cat_name;

        if (happiness > 80 && fullness > 80 && cleanliness > 80 && health > 80) {
            message += " и я счастлив как никогда! /ᐠ-⩊-マ₊˚⊹♡₊ ⊹";
        } else if (happiness < 10 || fullness < 10 || cleanliness < 10 || health < 10) {
            message += " и мне очень плохо! /ᐠﹷ ‸ ﹷ ᐟ";
            EM_ASM({
                alert("Игра окончена! Кот устал. Кот уходит. ᨐฅ");
            });
            emscripten_cancel_main_loop();
        } else {
            message += " и мои параметры:";
        }

        std::string status = "Счастье: " + std::to_string(happiness) +
                             "%, Сытость: " + std::to_string(fullness) +
                             "%, Ухоженность: " + std::to_string(cleanliness) +
                             "%, Здоровье: " + std::to_string(health) + "%";
        EM_ASM({
            document.getElementById("status").innerText = UTF8ToString($0);
            document.getElementById("dialogue").innerText = UTF8ToString($1);
        }, status.c_str(), message.c_str());
    }
    
    EMSCRIPTEN_KEEPALIVE
    void feed_cat() {
        fullness = std::min(100, fullness + 20);
        health = std::min(100, health + 10); 
        update_status();
    }

    EMSCRIPTEN_KEEPALIVE
    void play_cat() {
        happiness = std::min(100, happiness + 20);
        fullness = std::max(0, fullness - 10);
        cleanliness = std::max(0, cleanliness - 10);
        if (fullness < 20 || cleanliness < 20) {
            health = std::max(0, health - 5); 
        }
        update_status();
    }

    EMSCRIPTEN_KEEPALIVE
    void groom_cat() {
        cleanliness = std::min(100, cleanliness + 20);
        happiness = std::max(0, happiness - 10);
        health = std::min(100, health + 5); 
        update_status();
    }

    EMSCRIPTEN_KEEPALIVE
    void leave_cat() {
        fullness = std::max(0, fullness - 5);
        happiness = std::max(0, happiness - 5);
        cleanliness = std::max(0, cleanliness - 5);
        if (fullness < 20 || cleanliness < 20) {
            health = std::max(0, health - 5);
        }
        update_status();
    }

    EMSCRIPTEN_KEEPALIVE
    void set_cat_name(const char* name) {
        cat_name = std::string(name);
    }
    
}

int main() {
    emscripten_set_main_loop(update_status, 1, 1);
    return 0;
}
