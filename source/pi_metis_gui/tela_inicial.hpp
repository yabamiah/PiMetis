#ifndef TELA_INICIAL_HPP
#define TELA_INICIAL_HPP

#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include <vector>
#include <fstream>

#include "tela_camera.hpp"
#include "/home/yaba/Sandbox/PiMetis/source/pi_metis_ia/pi_metis_eyes.hpp"
#include "/home/yaba/Sandbox/PiMetis/source/pi_metis_ia/frame_provider.hpp"

class TelaInicial : public Gtk::Window
{
    public:
        TelaInicial(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade, FrameProvider& provider);
        static TelaInicial* create(FrameProvider& provider);

    protected:
        void on_ti_button1_clicked();
        void on_ti_button2_clicked();
        void on_ti_button3_clicked();
        void on_ti_button4_clicked();
        void on_ti_button5_clicked();
        void on_ti_button6_clicked();
        void on_ti_dialog2_button1_clicked();
        void on_ti_dialog2_button2_clicked();

        Gtk::Window *ti_window;
        Gtk::Dialog *ti_dialog1, *ti_dialog2;
        Gtk::Button *ti_button1, *ti_button2, *ti_button3, *ti_button4, *ti_button5, *ti_button6, *ti_dialog2_button1, *ti_dialog2_button2;
        Gtk::Entry *ti_dialog2_entry;
        Glib::RefPtr<Gtk::Builder> ti_builder;

    private:
        FrameProvider& frame_provider;
        // pi_metis_eyes eyes;
        // std::thread detection_thread;

        // void active_eyes_detect();
};


extern int *eyes_activate;
extern int limit_person;
#endif // TELA_INICIAL_HPP
