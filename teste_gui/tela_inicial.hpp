#ifndef TELA_INICIAL_HPP
#define TELA_INICIAL_HPP

#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <vector>

#include "tela_camera.hpp"

class TelaInicial : public Gtk::Window
{
    public:
        TelaInicial(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
        static TelaInicial* create();

    protected:
        void on_ti_button1_clicked();
        void on_ti_button2_clicked();
        void on_ti_button3_clicked();
        void on_ti_button4_clicked();

        Gtk::Window *ti_window;
        Gtk::Dialog *ti_dialog;
        Gtk::Button *ti_button1, *ti_button2, *ti_button3, *ti_button4;
        Glib::RefPtr<Gtk::Builder> ti_builder;
};

#endif // TELA_INICIAL_HPP
