// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>

#include "generator.hpp"
#include "parser.hpp"
#include "password.hpp"

struct PartRow {
    wxChoice* type;
    wxSpinCtrl* length;
    wxButton* remove;
};

class MainFrame : public wxFrame {
public:
    MainFrame();

private:
    // Preset templates
    wxChoice* m_presetChoice;
    // Visual builder
    wxScrolledWindow* m_builderPanel;
    wxBoxSizer* m_builderSizer;
    std::vector<PartRow> m_partRows;
    wxButton* m_addPartBtn;
    // Format field
    wxTextCtrl* m_formatCtrl;
    // Count
    wxSpinCtrl* m_countSpin;
    // Results
    wxTextCtrl* m_resultCtrl;
    // Buttons
    wxButton* m_generateBtn;
    wxButton* m_copyAllBtn;

    PasswordGenerator m_generator;

    bool m_syncingFromBuilder = false;
    bool m_syncingFromFormat = false;

    static const wxString PRESETS[];
    static const wxString PRESET_FORMATS[];
    static constexpr int NUM_PRESETS = 6;

    void AddPartRow(const wxString& type = "W", int length = 4);
    void RemovePartRow(int index);
    void RebuildBuilderFromFormat(const wxString& fmt);
    wxString BuildFormatFromBuilder() const;
    void RelayoutBuilder();

    // Event handlers
    void OnPresetSelected(wxCommandEvent& evt);
    void OnFormatChanged(wxCommandEvent& evt);
    void OnBuilderChanged(wxCommandEvent& evt);
    void OnAddPart(wxCommandEvent& evt);
    void OnRemovePart(wxCommandEvent& evt);
    void OnGenerate(wxCommandEvent& evt);
    void OnCopyAll(wxCommandEvent& evt);
};
