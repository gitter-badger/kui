#ifndef KUI_EVENT
#define KUI_EVENT

namespace kui {

  enum class Key {
  
    escape,
    backspace,
    
    space,
    exclaimation,
    double_quote,
    hash,
    dollar,
    percent,
    ampersand,
    single_quote,
    l_paren,
    r_paren,
    star,
    plus,
    comma,
    minus,
    dot,
    slash,

    key_0,
    key_1,
    key_2,
    key_3,
    key_4,
    key_5,
    key_6,
    key_7,
    key_8,
    key_9,
    
    colon,
    semicolon,
    l_angle,
    equal,
    r_angle,
    question,
    at,
    
    a,
    b,
    c, 
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p, 
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    
    l_square,
    backslash,
    r_square,
    carrot,
    underscore,
    tick,
    l_curly,
    pipe,
    r_curly,
    tilde,
    
    insert,
    del,
    home,
    end,
    page_up,
    page_down,
    
    up,
    down,
    right,
    left,
    
    tab,
    enter,
    
    f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12
  };
  
  class Key_event {
  public: 
    Key_event(Key key, bool shift = false, bool ctrl = false) {
      this->key = key;
      this->shift = shift;
      this->ctrl = ctrl;
    }
  
    Key key;
    bool shift;
    bool ctrl;
  };

}

#endif