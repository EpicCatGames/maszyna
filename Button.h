/*
This Source Code Form is subject to the
terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not
distributed with this file, You can
obtain one at
http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "Classes.h"
#include "sound.h"

class TButton
{ // animacja dwustanowa, włącza jeden z dwóch submodeli (jednego
    // z nich może nie być)
  private:
    TSubModel
        *pModelOn { nullptr },
        *pModelOff { nullptr }; // submodel dla stanu załączonego i wyłączonego
    bool m_state { false };
    bool const *bData { nullptr };
    int iFeedbackBit { 0 }; // Ra: bit informacji zwrotnej, do wyprowadzenia na pulpit
    sound_source m_soundfxincrease; // sound associated with increasing control's value
    sound_source m_soundfxdecrease; // sound associated with decreasing control's value
// methods
    // imports member data pair from the config file
    bool
        Load_mapping( cParser &Input );
    // plays the sound associated with current state
    void
        play();

  public:
    TButton() = default;
    void Clear(int const i = -1);
    inline void FeedbackBitSet(int const i) {
        iFeedbackBit = 1 << i; };
    void Turn( bool const State );
    inline
    bool Active() {
        return ( ( pModelOn != nullptr )
              || ( pModelOff != nullptr ) ); }
    void Update();
    void Init(std::string const &asName, TModel3d *pModel, bool bNewOn = false);
    void Load(cParser &Parser, TModel3d *pModel1, TModel3d *pModel2 = NULL);
    void AssignBool(bool const *bValue);
};

//---------------------------------------------------------------------------
