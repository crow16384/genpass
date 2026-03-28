// SPDX-License-Identifier: GPL-3.0-only

#include "main_frame.hpp"
#include "app_icon_xpm.hpp"
#include "parser.hpp"

#include <wx/clipbrd.h>
#include <wx/icon.h>
#include <wx/sizer.h>

// Preset labels and their format strings
const wxString MainFrame::PRESETS[] = {
    "W4s1d3 (Mixed)",
    "W5w4d3 (Words+digits)",
    "w6d2 (Simple)",
    "W8s2d4 (Strong)",
    "w4s1w4s1d2 (Compound)",
    "Custom",
};

const wxString MainFrame::PRESET_FORMATS[] = {
    "W4s1d3",
    "W5w4d3",
    "w6d2",
    "W8s2d4",
    "w4s1w4s1d2",
    "",
};

// IDs for events
enum {
    ID_PRESET = wxID_HIGHEST + 1,
    ID_FORMAT,
    ID_ADD_PART,
    ID_GENERATE,
    ID_COPY_ALL,
    ID_REMOVE_PART_BASE = wxID_HIGHEST + 100,
    ID_BUILDER_TYPE_BASE = wxID_HIGHEST + 200,
    ID_BUILDER_LEN_BASE = wxID_HIGHEST + 300,
};

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "GenPass — Password Generator",
              wxDefaultPosition, wxSize(520, 620))
{
    SetIcon(wxIcon(genpass_icon_xpm));

    auto* mainPanel = new wxPanel(this);
    auto* mainSizer = new wxBoxSizer(wxVERTICAL);

    // --- Preset row ---
    auto* presetSizer = new wxBoxSizer(wxHORIZONTAL);
    presetSizer->Add(new wxStaticText(mainPanel, wxID_ANY, "Preset:"),
                     0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
    m_presetChoice = new wxChoice(mainPanel, ID_PRESET, wxDefaultPosition,
                                  wxDefaultSize, NUM_PRESETS, PRESETS);
    m_presetChoice->SetSelection(0);
    presetSizer->Add(m_presetChoice, 1, wxEXPAND);
    mainSizer->Add(presetSizer, 0, wxEXPAND | wxALL, 8);

    // --- Visual template builder ---
    auto* builderLabel = new wxStaticText(mainPanel, wxID_ANY, "Template Builder:");
    mainSizer->Add(builderLabel, 0, wxLEFT | wxTOP, 8);

    m_builderPanel = new wxScrolledWindow(mainPanel, wxID_ANY,
                                          wxDefaultPosition, wxSize(-1, 160));
    m_builderPanel->SetScrollRate(0, 10);
    m_builderSizer = new wxBoxSizer(wxVERTICAL);
    m_builderPanel->SetSizer(m_builderSizer);

    mainSizer->Add(m_builderPanel, 0, wxEXPAND | wxLEFT | wxRIGHT, 8);

    m_addPartBtn = new wxButton(mainPanel, ID_ADD_PART, "+ Add Part");
    mainSizer->Add(m_addPartBtn, 0, wxLEFT | wxTOP | wxBOTTOM, 8);

    // --- Format field ---
    auto* formatSizer = new wxBoxSizer(wxHORIZONTAL);
    formatSizer->Add(new wxStaticText(mainPanel, wxID_ANY, "Format:"),
                     0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
    m_formatCtrl = new wxTextCtrl(mainPanel, ID_FORMAT);
    formatSizer->Add(m_formatCtrl, 1, wxEXPAND);
    mainSizer->Add(formatSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 8);

    // --- Count + Generate row ---
    auto* genSizer = new wxBoxSizer(wxHORIZONTAL);
    genSizer->Add(new wxStaticText(mainPanel, wxID_ANY, "Count:"),
                  0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 8);
    m_countSpin = new wxSpinCtrl(mainPanel, wxID_ANY, "3",
                                 wxDefaultPosition, wxSize(70, -1),
                                 wxSP_ARROW_KEYS, 1, 50, 3);
    genSizer->Add(m_countSpin, 0, wxRIGHT, 16);
    m_generateBtn = new wxButton(mainPanel, ID_GENERATE, "Generate");
    genSizer->Add(m_generateBtn, 0);
    mainSizer->Add(genSizer, 0, wxALL, 8);

    // --- Results ---
    auto* resultLabel = new wxStaticText(mainPanel, wxID_ANY, "Generated Passwords:");
    mainSizer->Add(resultLabel, 0, wxLEFT, 8);

    m_resultCtrl = new wxTextCtrl(mainPanel, wxID_ANY, "",
                                  wxDefaultPosition, wxSize(-1, 180),
                                  wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);
    m_resultCtrl->SetFont(wxFont(wxFontInfo(12).Family(wxFONTFAMILY_TELETYPE)));
    mainSizer->Add(m_resultCtrl, 1, wxEXPAND | wxLEFT | wxRIGHT, 8);

    // --- Copy button ---
    m_copyAllBtn = new wxButton(mainPanel, ID_COPY_ALL, "Copy All to Clipboard");
    mainSizer->Add(m_copyAllBtn, 0, wxALL, 8);

    mainPanel->SetSizer(mainSizer);

    // Bind events
    Bind(wxEVT_CHOICE,    &MainFrame::OnPresetSelected, this, ID_PRESET);
    Bind(wxEVT_TEXT,       &MainFrame::OnFormatChanged,  this, ID_FORMAT);
    Bind(wxEVT_BUTTON,    &MainFrame::OnAddPart,        this, ID_ADD_PART);
    Bind(wxEVT_BUTTON,    &MainFrame::OnGenerate,       this, ID_GENERATE);
    Bind(wxEVT_BUTTON,    &MainFrame::OnCopyAll,        this, ID_COPY_ALL);

    // Initialize with first preset
    m_formatCtrl->SetValue(PRESET_FORMATS[0]);
    RebuildBuilderFromFormat(PRESET_FORMATS[0]);

    SetMinSize(wxSize(420, 500));
}

void MainFrame::AddPartRow(const wxString& type, int length) {
    auto* rowSizer = new wxBoxSizer(wxHORIZONTAL);

    int idx = static_cast<int>(m_partRows.size());

    wxString types[] = {"W - Uppercase word", "w - Lowercase word",
                        "d - Digits", "s - Special"};
    auto* typeChoice = new wxChoice(m_builderPanel,
                                    ID_BUILDER_TYPE_BASE + idx,
                                    wxDefaultPosition, wxDefaultSize, 4, types);
    // Map type char to choice index
    if (type == "W") typeChoice->SetSelection(0);
    else if (type == "w") typeChoice->SetSelection(1);
    else if (type == "d") typeChoice->SetSelection(2);
    else if (type == "s") typeChoice->SetSelection(3);
    else typeChoice->SetSelection(0);

    auto* lenSpin = new wxSpinCtrl(m_builderPanel,
                                   ID_BUILDER_LEN_BASE + idx,
                                   wxString::Format("%d", length),
                                   wxDefaultPosition, wxSize(60, -1),
                                   wxSP_ARROW_KEYS, 1, 64, length);

    auto* removeBtn = new wxButton(m_builderPanel,
                                   ID_REMOVE_PART_BASE + idx,
                                   wxString::FromUTF8("\xE2\x9C\x95"),
                                   wxDefaultPosition, wxSize(30, -1));

    rowSizer->Add(typeChoice, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    rowSizer->Add(lenSpin, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
    rowSizer->Add(removeBtn, 0, wxALIGN_CENTER_VERTICAL);

    m_builderSizer->Add(rowSizer, 0, wxEXPAND | wxBOTTOM, 4);

    m_partRows.push_back({typeChoice, lenSpin, removeBtn});

    // Bind change handlers
    typeChoice->Bind(wxEVT_CHOICE, &MainFrame::OnBuilderChanged, this);
    lenSpin->Bind(wxEVT_SPINCTRL, &MainFrame::OnBuilderChanged, this);
    removeBtn->Bind(wxEVT_BUTTON, &MainFrame::OnRemovePart, this);
}

void MainFrame::RemovePartRow(int index) {
    if (index < 0 || index >= static_cast<int>(m_partRows.size()))
        return;

    auto& row = m_partRows[index];
    row.type->Destroy();
    row.length->Destroy();
    row.remove->Destroy();

    // Remove the sizer item for this row
    if (auto* item = m_builderSizer->GetItem(static_cast<size_t>(index)))
        m_builderSizer->Remove(index);

    m_partRows.erase(m_partRows.begin() + index);
    RelayoutBuilder();
}

void MainFrame::RebuildBuilderFromFormat(const wxString& fmt) {
    // Clear existing rows
    for (auto& row : m_partRows) {
        row.type->Destroy();
        row.length->Destroy();
        row.remove->Destroy();
    }
    m_builderSizer->Clear();
    m_partRows.clear();

    // Parse format string: each char in {W,w,d,s} optionally followed by digits
    std::string s = fmt.ToStdString();
    size_t i = 0;
    while (i < s.size()) {
        char c = s[i];
        if (c == 'W' || c == 'w' || c == 'd' || c == 's') {
            int len = 1;
            size_t j = i + 1;
            if (j < s.size() && std::isdigit(static_cast<unsigned char>(s[j]))) {
                len = 0;
                while (j < s.size() && std::isdigit(static_cast<unsigned char>(s[j]))) {
                    len = len * 10 + (s[j] - '0');
                    ++j;
                }
            }
            if (len < 1) len = 1;
            if (len > 64) len = 64;
            AddPartRow(wxString(1, c), len);
            i = j;
        } else {
            ++i;
        }
    }

    RelayoutBuilder();
}

wxString MainFrame::BuildFormatFromBuilder() const {
    wxString fmt;
    const char typeChars[] = {'W', 'w', 'd', 's'};
    for (const auto& row : m_partRows) {
        int sel = row.type->GetSelection();
        if (sel < 0 || sel > 3) sel = 0;
        fmt += wxString::Format("%c%d", typeChars[sel], row.length->GetValue());
    }
    return fmt;
}

void MainFrame::RelayoutBuilder() {
    m_builderPanel->FitInside();
    m_builderPanel->Layout();
    m_builderPanel->Refresh();
}

void MainFrame::OnPresetSelected(wxCommandEvent& evt) {
    int sel = m_presetChoice->GetSelection();
    if (sel < 0 || sel >= NUM_PRESETS) return;

    if (sel == NUM_PRESETS - 1) {
        // "Custom" — clear format, let user type
        m_formatCtrl->SetFocus();
        return;
    }

    wxString fmt = PRESET_FORMATS[sel];
    m_syncingFromBuilder = true;
    m_formatCtrl->SetValue(fmt);
    m_syncingFromBuilder = false;

    RebuildBuilderFromFormat(fmt);
}

void MainFrame::OnFormatChanged(wxCommandEvent& evt) {
    if (m_syncingFromBuilder) return;

    m_syncingFromFormat = true;
    RebuildBuilderFromFormat(m_formatCtrl->GetValue());
    m_syncingFromFormat = false;

    // Switch preset to "Custom" if no match
    wxString currentFmt = m_formatCtrl->GetValue();
    bool matched = false;
    for (int i = 0; i < NUM_PRESETS - 1; ++i) {
        if (currentFmt == PRESET_FORMATS[i]) {
            m_presetChoice->SetSelection(i);
            matched = true;
            break;
        }
    }
    if (!matched)
        m_presetChoice->SetSelection(NUM_PRESETS - 1);
}

void MainFrame::OnBuilderChanged(wxCommandEvent& evt) {
    if (m_syncingFromFormat) return;

    m_syncingFromBuilder = true;
    wxString fmt = BuildFormatFromBuilder();
    m_formatCtrl->SetValue(fmt);
    m_syncingFromBuilder = false;

    // Update preset selection
    bool matched = false;
    for (int i = 0; i < NUM_PRESETS - 1; ++i) {
        if (fmt == PRESET_FORMATS[i]) {
            m_presetChoice->SetSelection(i);
            matched = true;
            break;
        }
    }
    if (!matched)
        m_presetChoice->SetSelection(NUM_PRESETS - 1);
}

void MainFrame::OnAddPart(wxCommandEvent& evt) {
    AddPartRow("w", 4);
    RelayoutBuilder();

    m_syncingFromBuilder = true;
    m_formatCtrl->SetValue(BuildFormatFromBuilder());
    m_syncingFromBuilder = false;

    m_presetChoice->SetSelection(NUM_PRESETS - 1);
}

void MainFrame::OnRemovePart(wxCommandEvent& evt) {
    wxObject* obj = evt.GetEventObject();
    for (int i = 0; i < static_cast<int>(m_partRows.size()); ++i) {
        if (m_partRows[i].remove == obj) {
            RemovePartRow(i);

            m_syncingFromBuilder = true;
            m_formatCtrl->SetValue(BuildFormatFromBuilder());
            m_syncingFromBuilder = false;

            m_presetChoice->SetSelection(NUM_PRESETS - 1);
            break;
        }
    }
}

void MainFrame::OnGenerate(wxCommandEvent& evt) {
    wxString fmt = m_formatCtrl->GetValue().Trim();
    if (fmt.IsEmpty()) {
        wxMessageBox("Please enter a format or select a preset.",
                     "No Format", wxOK | wxICON_WARNING, this);
        return;
    }

    int count = m_countSpin->GetValue();
    PasswordTemplate tpl = Parser::parse(fmt.ToStdString());

    wxString result;
    for (int i = 0; i < count; ++i) {
        result += wxString::FromUTF8(m_generator.generate(tpl));
        if (i < count - 1) result += "\n";
    }

    m_resultCtrl->SetValue(result);
}

void MainFrame::OnCopyAll(wxCommandEvent& evt) {
    wxString text = m_resultCtrl->GetValue();
    if (text.IsEmpty()) return;

    if (wxTheClipboard->Open()) {
        wxTheClipboard->SetData(new wxTextDataObject(text));
        wxTheClipboard->Close();
    }
}
