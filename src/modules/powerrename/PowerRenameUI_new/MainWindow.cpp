﻿#include "pch.h"
#include "MainWindow.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PowerRenameUI_new::implementation
{
    MainWindow::MainWindow()
    {
        m_explorerItems = winrt::single_threaded_observable_vector<PowerRenameUI_new::ExplorerItem>();
        m_searchRegExShortcuts = winrt::single_threaded_observable_vector<PowerRenameUI_new::RegExShortcut>();
        m_fileRegExShortcuts = winrt::single_threaded_observable_vector<PowerRenameUI_new::RegExShortcut>();

        //auto folder = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(0, L"New Folder", 0);
        //folder.Children();
        //folder.Children().Append(winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(1, L"a.txt", 1));
        //folder.Children().Append(winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(2, L"b.txt", 1));
        //folder.Children().Append(winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(3, L"c.txt", 1));
        //m_explorerItems.Append(folder);
        //m_explorerItems.Append(winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(4, L"1.txt", 1));
        //m_explorerItems.Append(winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(5, L"2.txt", 1));
        //m_explorerItems.Append(winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(6, L"3.txt", 1));

        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\.", L"Matches any character"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\d", L"Any digit, short for [0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\D", L"A non-digit, short for [^0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\w", L"A non-whitespace character, short for [^\\s]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\S", L"A word character, short for [a-zA-Z_0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\S+", L"Several non-whitespace characters"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\b", L"Matches a word boundary where a word character is [a-zA-Z0-9_]."));

        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$YYYY", L"Year"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$MM", L"Month"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$DD", L"Day"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$hh", L"Hours"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$mm", L"Minutes"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$ss", L"Seconds"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$fff", L"Milliseconds"));
        InitializeComponent();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::ExplorerItem> MainWindow::ExplorerItems()
    {
        return m_explorerItems;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::RegExShortcut> MainWindow::SearchRegExShortcuts()
    {
        return m_searchRegExShortcuts;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::RegExShortcut> MainWindow::FileRegExShortcuts()
    {
        return m_fileRegExShortcuts;
    }

    void MainWindow::AddExplorerItem(int32_t id, hstring const& original, int32_t type, int32_t parentId)
    {
        auto newItem = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(id, original, type);
        if (parentId == 0)
        {
            m_explorerItems.Append(newItem);
        }
        else
        {
            auto parent = FindById(parentId);
            parent.Children().Append(newItem);
        }
    }
}

void winrt::PowerRenameUI_new::implementation::MainWindow::Click_rename(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
    m_explorerItems.Append(winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(4, L"1212121.txt", 0));
}

PowerRenameUI_new::ExplorerItem winrt::PowerRenameUI_new::implementation::MainWindow::FindById(int32_t id)
{
    auto fakeRoot = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(0, L"Fake", 0);
    fakeRoot.Children(m_explorerItems);
    return FindById(fakeRoot, id);
}

PowerRenameUI_new::ExplorerItem winrt::PowerRenameUI_new::implementation::MainWindow::FindById(PowerRenameUI_new::ExplorerItem& root, int32_t id)
{
    if (root.Id() == id)
        return root;

    if (root.Type() == static_cast<UINT>(ExplorerItem::ExplorerItemType::Folder))
    {
        for (auto c : root.Children())
        {
            auto result = FindById(c, id);
            if (result != NULL)
                return result;
        }
    }

    return NULL;
}
