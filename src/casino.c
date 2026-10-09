#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/rtc.h>
#include <stdint.h>
#include <stdio.h>

#define STARTING_CREDITS 1000
#define FREE_CREDIT_BONUS 500
#define MIN_BET 10
#define MAX_CREDITS 999999

static int credits = STARTING_CREDITS;
static int bet = 50;
static uint32_t random_state;
static char last_result[64] = "Choose a game and press EXE to play.";
static int exit_requested;

static uint32_t random_next(void)
{
    random_state ^= random_state << 13;
    random_state ^= random_state >> 17;
    random_state ^= random_state << 5;
    return random_state;
}

static int random_below(int limit)
{
    return (int)(random_next() % (uint32_t)limit);
}

static void draw_header(const char *title)
{
    dclear(C_WHITE);
    drect(0, 0, 383, 25, C_BLACK);
    dtext(10, 5, C_WHITE, title);
}

static void draw_balance(void)
{
    char text[40];
    snprintf(text, sizeof text, "CREDITS: %d", credits);
    dtext(245, 5, C_WHITE, text);
}

static void draw_game(const char *title, const char *message)
{
    char text[40];

    draw_header(title);
    draw_balance();
    dtext(10, 38, C_BLUE, "VIRTUAL CREDITS ONLY - NO REAL MONEY");
    snprintf(text, sizeof text, "BET: %d credits", bet);
    dtext(10, 62, C_BLACK, text);
    dtext(10, 105, C_BLACK, message);
    dtext(10, 158, C_BLUE, "LEFT/RIGHT: bet -/+10   [0]: free +500");
    dtext(10, 181, C_BLACK, "[EXE]: play   [EXIT]: games   [MENU]: quit");
}

static void adjust_bet(int amount)
{
    bet += amount;
    if(bet < MIN_BET) bet = MIN_BET;
    if(bet > credits) bet = credits;
    if(bet < MIN_BET && credits >= MIN_BET) bet = MIN_BET;
}

static void add_free_credits(void)
{
    if(credits <= MAX_CREDITS - FREE_CREDIT_BONUS)
        credits += FREE_CREDIT_BONUS;
    else
        credits = MAX_CREDITS;
    snprintf(last_result, sizeof last_result, "+%d free credits added.", FREE_CREDIT_BONUS);
}

static int start_wager(void)
{
    if(credits < MIN_BET) {
        snprintf(last_result, sizeof last_result, "Out of credits. Press 0 for a free +500.");
        return 0;
    }
    if(bet > credits) bet = credits;
    credits -= bet;
    return 1;
}

static void award_winnings(int multiplier)
{
    int winnings = bet * multiplier;
    if(credits <= MAX_CREDITS - winnings)
        credits += winnings;
    else
        credits = MAX_CREDITS;
}

static void handle_common_key(int key)
{
    if(key == KEY_LEFT) adjust_bet(-10);
    if(key == KEY_RIGHT) adjust_bet(10);
    if(key == KEY_0) add_free_credits();
    if(key == KEY_MENU) exit_requested = 1;
}

static void play_slots(void)
{
    static const char *symbols[] = {"7", "BAR", "STAR", "BELL", "CHERRY", "GEM"};
    char reel_text[48] = "[ ? ]    [ ? ]    [ ? ]";

    while(!exit_requested) {
        key_event_t event;
        draw_game("Z CASINO | SLOTS", last_result);
        dtext(10, 80, C_RED, reel_text);
        dupdate();
        event = getkey();

        if(event.key == KEY_EXIT) return;
        handle_common_key(event.key);
        if(event.key != KEY_EXE || exit_requested) continue;
        if(!start_wager()) continue;

        int first = random_below(6);
        int second = random_below(6);
        int third = random_below(6);
        snprintf(reel_text, sizeof reel_text, "[ %s ]  [ %s ]  [ %s ]",
            symbols[first], symbols[second], symbols[third]);

        if(first == second && second == third) {
            award_winnings(5);
            snprintf(last_result, sizeof last_result, "JACKPOT! Returned 5x your bet!");
        }
        else if(first == second || second == third || first == third) {
            award_winnings(2);
            snprintf(last_result, sizeof last_result, "Pair! Returned 2x your bet.");
        }
        else {
            snprintf(last_result, sizeof last_result, "No match. Try again with credits.");
        }
    }
}

static void play_dice(void)
{
    int high = 0;
    char message[64] = "Choose 1=LOW or 2=HIGH, then press EXE.";

    while(!exit_requested) {
        key_event_t event;
        draw_game("Z CASINO | DICE", last_result);
        dtext(10, 82, C_BLACK, high ? "PICK: HIGH (8-12)" : "PICK: LOW (2-6)");
        dtext(10, 108, C_BLACK, message);
        dupdate();
        event = getkey();

        if(event.key == KEY_EXIT) return;
        handle_common_key(event.key);
        if(event.key == KEY_1) high = 0;
        if(event.key == KEY_2) high = 1;
        if(event.key != KEY_EXE || exit_requested || !start_wager()) continue;

        int roll = random_below(6) + random_below(6) + 2;
        snprintf(message, sizeof message, "Dice total: %d", roll);
        if((!high && roll >= 2 && roll <= 6) || (high && roll >= 8)) {
            award_winnings(2);
            snprintf(last_result, sizeof last_result, "WIN! Returned 2x your bet.");
        }
        else {
            snprintf(last_result, sizeof last_result, "No win. A 7 loses this round.");
        }
    }
}

static int is_red(int number)
{
    static const int red_numbers[] = {
        1, 3, 5, 7, 9, 12, 14, 16, 18,
        19, 21, 23, 25, 27, 30, 32, 34, 36
    };
    for(int i = 0; i < 18; i++)
        if(red_numbers[i] == number) return 1;
    return 0;
}

static void play_roulette(void)
{
    int pick_red = 1;
    char outcome[48] = "Press 1 for RED or 2 for BLACK.";

    while(!exit_requested) {
        key_event_t event;
        draw_game("Z CASINO | ROULETTE", last_result);
        dtext(10, 82, pick_red ? C_RED : C_BLACK,
            pick_red ? "YOUR PICK: RED" : "YOUR PICK: BLACK");
        dtext(10, 108, C_BLACK, outcome);
        dupdate();
        event = getkey();

        if(event.key == KEY_EXIT) return;
        handle_common_key(event.key);
        if(event.key == KEY_1) pick_red = 1;
        if(event.key == KEY_2) pick_red = 0;
        if(event.key != KEY_EXE || exit_requested || !start_wager()) continue;

        int number = random_below(37);
        int landed_red = is_red(number);
        snprintf(outcome, sizeof outcome, "Ball landed on %d (%s).", number,
            number == 0 ? "GREEN" : landed_red ? "RED" : "BLACK");
        if(number != 0 && landed_red == pick_red) {
            award_winnings(2);
            snprintf(last_result, sizeof last_result, "WIN! Returned 2x your bet.");
        }
        else {
            snprintf(last_result, sizeof last_result, "No win. Your bet was lost.");
        }
    }
}

int main(void)
{
    random_state = rtc_ticks() ^ 0x9e3779b9u;
    if(random_state == 0) random_state = 1;

    while(!exit_requested) {
        key_event_t event;
        draw_header("Z CASINO - VIRTUAL CREDITS");
        draw_balance();
        dtext(10, 45, C_BLUE, "FAKE CREDITS ONLY. NO REAL MONEY OR PAYOUTS.");
        dtext(10, 78, C_BLACK, "1. Slots");
        dtext(10, 100, C_BLACK, "2. Dice: low or high");
        dtext(10, 122, C_BLACK, "3. Roulette: red or black");
        dtext(10, 158, C_BLACK, "Select a game with 1, 2, or 3.");
        dtext(10, 181, C_BLACK, "[0]: add 500 free credits   [MENU]: quit");
        dupdate();

        event = getkey();
        if(event.key == KEY_MENU) break;
        if(event.key == KEY_0) add_free_credits();
        if(event.key == KEY_1) play_slots();
        if(event.key == KEY_2) play_dice();
        if(event.key == KEY_3) play_roulette();
    }
    return 1;
}