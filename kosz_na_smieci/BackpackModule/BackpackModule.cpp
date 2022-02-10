#include <Python.h>

/*
 * Implements an example function.
 */
PyDoc_STRVAR(BackpackModule_example_doc, "example(obj, number)\
\
Example function");

PyObject *BackpackModule_example(PyObject *self, PyObject *args, PyObject *kwargs) {
    /* Shared references that do not need Py_DECREF before returning. */
    PyObject *obj = NULL;
    int number = 0;

    /* Parse positional and keyword arguments */
    static char* keywords[] = { "obj", "number", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", keywords, &obj, &number)) {
        return NULL;
    }

    /* Function implementation starts here */

    if (number < 0) {
        PyErr_SetObject(PyExc_ValueError, obj);
        return NULL;    /* return NULL indicates error */
    }

    Py_RETURN_NONE;
}

/*
 * List of functions to add to BackpackModule in exec_BackpackModule().
 */
static PyMethodDef BackpackModule_functions[] = {
    { "example", (PyCFunction)BackpackModule_example, METH_VARARGS | METH_KEYWORDS, BackpackModule_example_doc },
    { NULL, NULL, 0, NULL } /* marks end of array */
};

/*
 * Initialize BackpackModule. May be called multiple times, so avoid
 * using static state.
 */
int exec_BackpackModule(PyObject *module) {
    PyModule_AddFunctions(module, BackpackModule_functions);

    PyModule_AddStringConstant(module, "__author__", "kamil");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2022);

    return 0; /* success */
}

/*
 * Documentation for BackpackModule.
 */
PyDoc_STRVAR(BackpackModule_doc, "The BackpackModule module");


static PyModuleDef_Slot BackpackModule_slots[] = {
    { Py_mod_exec, exec_BackpackModule },
    { 0, NULL }
};

static PyModuleDef BackpackModule_def = {
    PyModuleDef_HEAD_INIT,
    "BackpackModule",
    BackpackModule_doc,
    0,              /* m_size */
    NULL,           /* m_methods */
    BackpackModule_slots,
    NULL,           /* m_traverse */
    NULL,           /* m_clear */
    NULL,           /* m_free */
};

PyMODINIT_FUNC PyInit_BackpackModule() {
    return PyModuleDef_Init(&BackpackModule_def);
}
