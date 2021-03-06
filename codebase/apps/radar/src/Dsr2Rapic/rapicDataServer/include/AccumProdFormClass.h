
//////////////////////////////////////////////////////////////
//
// Header file for AccumProdFormClass
//
//    This file is generated by RapidApp 1.2
//
//    This class is derived from AccumProdFormClassUI which 
//    implements the user interface created in 
//    RapidApp. This class contains virtual
//    functions that are called from the user interface.
//
//    When you modify this header file, limit your changes to those
//    areas between the "//---- Start/End editable code block" markers
//
//    This will allow RapidApp to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//////////////////////////////////////////////////////////////
#ifndef ACCUMPRODFORMCLASS_H
#define ACCUMPRODFORMCLASS_H
#include "AccumProdFormClassUI.h"
//---- Start editable code block: headers and declarations

#include "rain_acc.h"

//---- End editable code block: headers and declarations


//---- AccumProdFormClass class declaration

class AccumProdFormClass : public AccumProdFormClassUI
{

  public:

    AccumProdFormClass ( const char *, Widget );
    AccumProdFormClass ( const char * );
    ~AccumProdFormClass();
    const char *  className();

    static VkComponent *CreateAccumProdFormClass( const char *name, Widget parent ); 

    //---- Start editable code block: AccumProdFormClass public
    
    /*
     * SetProd initialises LocalAccumProduct 
     * This dialog updates LocalAccumProduct
     */
    void	    SetProd(accum_product *setprod);
    accum_product   LocalAccumProduct;

    /*
     *	UpdateProd copies the contents of LocalAccumProduct to getprod
     *	or EditAccumProduct if getprod not defined
     *	EditAccumProduct is a pointer to the original product class
     */
    void	    ReturnProd(accum_product *retprod = 0);
    accum_product   *EditAccumProduct;
    
    /*
     * write new values to display
     */
    void	    UpdateForm();

    //---- End editable code block: AccumProdFormClass public



  protected:


    // These functions will be called as a result of callbacks
    // registered in AccumProdFormClassUI

    virtual void uifAccPeriod12hr ( Widget, XtPointer );
    virtual void uifAccPeriod1hr ( Widget, XtPointer );
    virtual void uifAccPeriod24hr ( Widget, XtPointer );
    virtual void uifAccPeriod2hr ( Widget, XtPointer );
    virtual void uifAccPeriod30min ( Widget, XtPointer );
    virtual void uifAccPeriod3hr ( Widget, XtPointer );
    virtual void uifAccPeriod6hr ( Widget, XtPointer );
    virtual void uifAccumOnTheHour ( Widget, XtPointer );
    virtual void uifAccumPeriodText ( Widget, XtPointer );
    virtual void uifAccumRunning ( Widget, XtPointer );
    virtual void uifCAPPIHeightText ( Widget, XtPointer );
    virtual void uifCAPPIHt0 ( Widget, XtPointer );
    virtual void uifCAPPIHt1000 ( Widget, XtPointer );
    virtual void uifCAPPIHt1500 ( Widget, XtPointer );
    virtual void uifCAPPIHt3000 ( Widget, XtPointer );
    virtual void uifCAPPIHt500 ( Widget, XtPointer );
    virtual void uifCAPPIHt5000 ( Widget, XtPointer );
    virtual void uifRainRateClipText ( Widget, XtPointer );
    virtual void uifUseAll ( Widget, XtPointer );
    virtual void uifVolOnly ( Widget, XtPointer );

    //---- Start editable code block: AccumProdFormClass protected


    //---- End editable code block: AccumProdFormClass protected



  private:

    static void* RegisterAccumProdFormClassInterface();

    //---- Start editable code block: AccumProdFormClass private


    //---- End editable code block: AccumProdFormClass private


};
//---- Start editable code block: End of generated code


//---- End editable code block: End of generated code

#endif

