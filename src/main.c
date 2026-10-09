#include <gint/display.h>
#include <gint/keyboard.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *notes_pages[] = {
    // PAGE 1: STORES & PATHWAYS
    "IGCSE PHYSICS - TOPIC 4: ENERGY\n"
    "GRADE 9 TRIPLE SCIENCE REVISION NOTES\n"
    "========================================\n\n"
    "THE 8 ENERGY STORES:\n"
    "- CHEMICAL: Stored in chemicals. Food, petrol, batteries, coal.\n"
    "- KINETIC: Moving objects. Moving car, runner, rolling ball.\n"
    "- GPE: Height/position in gravitational field. Raised weight.\n"
    "- ELASTIC POTENTIAL: Stretched or compressed spring/bow.\n"
    "- THERMAL (INTERNAL): Particles inside substance. Hot water/pan.\n"
    "- MAGNETIC: Magnetic fields and interacting magnets.\n"
    "- ELECTROSTATIC: Electric charges and electric fields.\n"
    "- NUCLEAR: Stored in atomic nuclei. Sun reactions, nuclear fuel.\n\n"
    "THE 4 TRANSFER PATHWAYS:\n"
    "- MECHANICALLY: Force doing work (pushing a box, lifting).\n"
    "- ELECTRICALLY: Electric current (battery powering a motor).\n"
    "- BY HEATING: Temp difference, hotter to cooler (hot pan).\n"
    "- BY RADIATION: EM waves, infrared or visible light (Sun).",

    // PAGE 2: CONSERVATION, EFFICIENCY & SANKEY
    "CONSERVATION OF ENERGY & EFFICIENCY\n"
    "========================================\n\n"
    "IMPORTANT RULE:\n"
    "Energy cannot be created or destroyed. It can only be transferred\n"
    "between stores or spread into the surroundings.\n\n"
    "KEY WORD: DISSIPATED\n"
    "Energy spreads into surroundings and becomes less useful.\n"
    "Exam Answer: 'Energy is not destroyed. It is transferred to the\n"
    "surroundings, mainly as thermal energy and sound.'\n\n"
    "EFFICIENCY FORMULAS:\n"
    "- Efficiency (%) = (useful energy output / total input) x 100\n"
    "- Efficiency (%) = (useful power output / total power) x 100\n\n"
    "SANKEY DIAGRAMS:\n"
    "- Incoming arrow = total input energy.\n"
    "- Forward arrow = useful energy | Side/Down = wasted energy.\n"
    "- Arrow width represents energy amount.\n"
    "- Total input = useful output + wasted output.\n\n"
    "HOW TO IMPROVE EFFICIENCY:\n"
    "- Lubricate moving parts to reduce friction.\n"
    "- Insulate hot parts to reduce heat loss.\n"
    "- Reduce electrical resistance.",

    // PAGE 3: FORMULAS & CALCULATIONS
    "WORK, GPE, KE & POWER FORMULAS\n"
    "========================================\n\n"
    "WORK DONE:\n"
    "W = F x d   [Joules = Newtons x meters]\n"
    "F = W / d   |   d = W / F\n"
    "No work done if object does not move or moves at 90 deg to force.\n\n"
    "GRAVITATIONAL POTENTIAL ENERGY (GPE):\n"
    "GPE = m x g x h   (g = 9.8 or 10 N/kg on Earth)\n"
    "m = GPE / (g x h)   |   h = GPE / (m x g)\n"
    "Use vertical height, not slope length!\n\n"
    "KINETIC ENERGY (KE):\n"
    "KE = 0.5 x m x v^2   [v^2 = v x v]\n"
    "m = 2 x KE / v^2   |   v = sqrt(2 x KE / m)\n"
    "If speed doubles, KE becomes 4 times larger!\n\n"
    "POWER:\n"
    "P = E / t   or   P = W / t   [Watts = Joules / seconds]\n\n"
    "CONVERSIONS:\n"
    "- Mass: g / 1000 = kg  |  Distance: cm / 100 = m\n"
    "- Speed: km/h / 3.6 = m/s  |  Time: 1 min = 60 s",

    // PAGE 4: THERMAL TRANSFERS
    "THERMAL ENERGY TRANSFERS\n"
    "========================================\n\n"
    "CONDUCTION (Solids/Metals):\n"
    "- Particles vibrate and pass energy to neighbours.\n"
    "- Metals have free electrons that transfer energy by collisions.\n\n"
    "CONVECTION (Liquids & Gases only):\n"
    "- Fluid near heater warms, expands, becomes less dense and rises.\n"
    "- Cooler, denser fluid sinks to replace it, forming a current.\n"
    "- Does NOT occur in solids.\n\n"
    "RADIATION (EM Infrared Waves):\n"
    "- Does not need particles; travels through a vacuum (e.g. Sun).\n"
    "- Black, Matt surfaces: Good absorbers & good emitters.\n"
    "- White, Shiny surfaces: Poor absorbers & emitters, reflect IR.\n\n"
    "INSULATION EXAMPLES:\n"
    "- Loft / Cavity Wall: Traps air to reduce conduction & convection.\n"
    "- Vacuum Flask: Vacuum stops conduction/convection; shiny walls\n"
    "  reflect radiation; stopper reduces conduction/convection.",

    // PAGE 5: PRACTICALS & GRAPH SKILLS
    "CAN PRACTICAL & GRAPH SKILLS\n"
    "========================================\n\n"
    "COOLING CAN PRACTICAL:\n"
    "- IV: Surface type/colour (black matt vs shiny).\n"
    "- DV: Water temp over time / temp drop in fixed time.\n"
    "- Controls: Starting temp, volume of water, room temp, lid.\n"
    "- Conclusion: Black matt can cools faster (better emitter of IR).\n"
    "- Reliability: Repeat 3x, spot anomalies, calculate mean.\n"
    "- Validity: Fair test (change only IV).\n\n"
    "GRAPH SKILLS:\n"
    "- Line Graph = Continuous data | Bar Chart = Categories.\n"
    "- Gradient = change in y / change in x (rise / run).\n"
    "- Temperature-time gradient = change in temp / change in time.\n"
    "- Steeper downward line = faster rate of cooling.\n"
    "- Tangent: Draw straight line touching curve to find gradient at point.",

    // PAGE 6: ENERGY RESOURCES
    "ENERGY RESOURCES SUMMARY\n"
    "========================================\n\n"
    "RENEWABLE (Replaced naturally on human timescale):\n"
    "- Wind, Hydroelectric, Tidal, Wave, Geothermal, Solar.\n"
    "- Advantages: No fuel burned, no CO2 during operation.\n"
    "- Disadvantages: Weather/location dependent, visual/habitat impact.\n\n"
    "NON-RENEWABLE (Finite supply, cannot replace quickly):\n"
    "- Fossil Fuels (Coal, Oil, Gas) & Nuclear (Uranium).\n"
    "- Advantages: Reliable, high energy output, established.\n"
    "- Disadvantages: CO2 climate change (fossil), radioactive waste (nuclear)."
};

#define TOTAL_PAGES 6

void draw_header(const char *title) {
    dclear(C_WHITE);
    drect(0, 0, 395, 24, C_BLACK);
    dtext(10, 5, C_WHITE, title);
}

void run_equation_solver(int formula_type) {
    float v2 = 5.0f, v3 = 2.0f, v4 = 3.0f;
    int target_var = 1;

    while(1) {
        draw_header("PHYSICS PREPARED SOLVER");
        char buf[128];

        if(formula_type == 1) {
            dtext(10, 30, C_BLACK, "FORMULA: Work (W) = Force (F) * distance (d)");
            sprintf(buf, "[F1] Work (W): %s", (target_var == 1) ? "?" : "CALCULATE");
            dtext(10, 55, (target_var == 1) ? C_RED : C_BLACK, buf);
            sprintf(buf, "[F2] Force (F): %.2f N %s", v2, (target_var == 2) ? "(?)" : "");
            dtext(10, 75, (target_var == 2) ? C_RED : C_BLACK, buf);
            sprintf(buf, "[F3] Distance (d): %.2f m %s", v3, (target_var == 3) ? "(?)" : "");
            dtext(10, 95, (target_var == 3) ? C_RED : C_BLACK, buf);
            dtext(10, 130, C_BLUE, "[F1-F3]: Set Unknown (?) | [EXE]: Solve");
            dtext(10, 150, C_BLACK, "[+] / [-]: Adjust Input Values");
        }
        else if(formula_type == 2) {
            dtext(10, 30, C_BLACK, "FORMULA: GPE = mass (m) * g * height (h)");
            sprintf(buf, "[F1] GPE: %s", (target_var == 1) ? "?" : "CALCULATE");
            dtext(10, 50, (target_var == 1) ? C_RED : C_BLACK, buf);
            sprintf(buf, "[F2] Mass (m): %.2f kg %s", v2, (target_var == 2) ? "(?)" : "");
            dtext(10, 70, (target_var == 2) ? C_RED : C_BLACK, buf);
            sprintf(buf, "[F3] Gravity (g): %.1f N/kg %s", (v3 == 0.0f) ? 10.0f : v3, (target_var == 3) ? "(?)" : "");
            dtext(10, 90, (target_var == 3) ? C_RED : C_BLACK, buf);
            sprintf(buf, "[F4] Height (h): %.2f m %s", v4, (target_var == 4) ? "(?)" : "");
            dtext(10, 110, (target_var == 4) ? C_RED : C_BLACK, buf);
            dtext(10, 140, C_BLUE, "[F1-F4]: Set Unknown (?) | [EXE]: Solve");
        }
        else if(formula_type == 3) {
            dtext(10, 30, C_BLACK, "FORMULA: KE = 0.5 * mass (m) * speed^2 (v)");
            sprintf(buf, "[F1] KE: %s", (target_var == 1) ? "?" : "CALCULATE");
            dtext(10, 55, (target_var == 1) ? C_RED : C_BLACK, buf);
            sprintf(buf, "[F2] Mass (m): %.2f kg %s", v2, (target_var == 2) ? "(?)" : "");
            dtext(10, 75, (target_var == 2) ? C_RED : C_BLACK, buf);
            sprintf(buf, "[F3] Speed (v): %.2f m/s %s", v3, (target_var == 3) ? "(?)" : "");
            dtext(10, 95, (target_var == 3) ? C_RED : C_BLACK, buf);
            dtext(10, 130, C_BLUE, "[F1-F3]: Set Unknown (?) | [EXE]: Solve");
        }

        dtext(10, 195, C_BLUE, "[EXIT]: Back | [MENU]: Exit to Calculator");
        dupdate();

        key_event_t ev = getkey();
        if(ev.key == KEY_MENU || ev.key == KEY_EXIT) return;

        if(ev.key == KEY_F1) target_var = 1;
        if(ev.key == KEY_F2) target_var = 2;
        if(ev.key == KEY_F3) target_var = 3;
        if(ev.key == KEY_F4) target_var = 4;

        if(ev.key == KEY_PLUS) { v2 += 1.0f; v3 += 1.0f; }
        if(ev.key == KEY_MINUS) { if(v2 > 0) v2 -= 1.0f; if(v3 > 0) v3 -= 1.0f; }

        if(ev.key == KEY_EXE) {
            while(1) {
                draw_header("CALCULATION RESULTS");

                if(formula_type == 1) {
                    if(target_var == 1) {
                        float res = v2 * v3;
                        sprintf(buf, "W = F * d = %.2f N * %.2f m", v2, v3);
                        dtext(10, 50, C_BLACK, buf);
                        sprintf(buf, "RESULT: Work Done = %.2f Joules", res);
                        dtext(10, 80, C_DARK, buf);
                    }
                }
                else if(formula_type == 2) {
                    float g = (v3 == 0.0f) ? 10.0f : v3;
                    if(target_var == 1) {
                        float res = v2 * g * v4;
                        sprintf(buf, "GPE = m * g * h = %.1f * %.1f * %.1f", v2, g, v4);
                        dtext(10, 50, C_BLACK, buf);
                        sprintf(buf, "RESULT: GPE = %.2f Joules", res);
                        dtext(10, 80, C_DARK, buf);
                    }
                }
                else if(formula_type == 3) {
                    if(target_var == 1) {
                        float res = 0.5f * v2 * (v3 * v3);
                        sprintf(buf, "KE = 0.5 * %.1f * (%.1f)^2", v2, v3);
                        dtext(10, 50, C_BLACK, buf);
                        sprintf(buf, "RESULT: Kinetic Energy = %.2f Joules", res);
                        dtext(10, 80, C_DARK, buf);
                    }
                }

                dtext(10, 160, C_BLACK, "Press [EXE] or [EXIT] to go back.");
                dtext(10, 180, C_RED, "Press [MENU] to quit to calculator OS.");
                dupdate();

                key_event_t ev2 = getkey();
                if(ev2.key == KEY_MENU) return;
                if(ev2.key == KEY_EXE || ev2.key == KEY_EXIT) break;
            }
        }
    }
}

void run_calculator() {
    while(1) {
        draw_header("PHYSICS FORMULA CALCULATOR");

        dtext(10, 35, C_BLACK, "1. Work Done (W = F * d)");
        dtext(10, 55, C_BLACK, "2. GPE (GPE = m * g * h)");
        dtext(10, 75, C_BLACK, "3. Kinetic Energy (KE = 0.5 * m * v^2)");
        dtext(10, 130, C_BLACK, "[1-3]: Choose Formula");
        dtext(10, 160, C_BLUE, "[MENU]: Exit to main CG50 launcher");
        dupdate();

        key_event_t ev = getkey();
        if(ev.key == KEY_MENU) return;

        if(ev.key == KEY_1) run_equation_solver(1);
        if(ev.key == KEY_2) run_equation_solver(2);
        if(ev.key == KEY_3) run_equation_solver(3);
    }
}

void show_notes() {
    int page = 0;
    while(1) {
        draw_header("IGCSE PHYSICS TOPIC 4 NOTES");

        char buffer[1500];
        strcpy(buffer, notes_pages[page]);
        char *line = strtok(buffer, "\n");
        int y = 32;

        while(line != NULL && y < 190) {
            dtext(10, y, C_BLACK, line);
            y += 12;
            line = strtok(NULL, "\n");
        }

        char page_str[32];
        sprintf(page_str, "Page %d of %d", page + 1, TOTAL_PAGES);
        dtext(10, 205, C_BLUE, page_str);
        dtext(220, 205, C_BLUE, "[< >] Nav | [MENU] Exit");
        dupdate();

        key_event_t ev = getkey();
        if(ev.key == KEY_MENU) return;
        if(ev.key == KEY_RIGHT && page < TOTAL_PAGES - 1) page++;
        if(ev.key == KEY_LEFT && page > 0) page--;
        if(ev.key == KEY_EXIT) return;
    }
}

int main() {
    while(1) {
        draw_header("IGCSE PHYSICS GRADE 9 TRIPLE");

        dtext(10, 40, C_BLACK, "1. View Revision Notes");
        dtext(10, 60, C_BLACK, "2. Formula Calculator & Solver");
        dtext(10, 110, C_BLACK, "Press [1] or [2] to select.");
        dtext(10, 170, C_RED, "Press [MENU] at any time to exit.");
        dupdate();

        key_event_t ev = getkey();

        if(ev.key == KEY_MENU) break;
        if(ev.key == KEY_1) show_notes();
        if(ev.key == KEY_2) run_calculator();
    }
    return 0;
}
