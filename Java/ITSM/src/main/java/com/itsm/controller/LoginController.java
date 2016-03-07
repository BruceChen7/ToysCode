package com.itsm.controller;

import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.stereotype.Controller;

import javax.servlet.http.HttpServletRequest;

/**
 * Created by CM on 2016/3/2.
 */
@Controller
@RequestMapping("itsm")
public class LoginController {

    @RequestMapping("login")
    public String loginItsm(HttpServletRequest request, ModelMap model) {
        return "login";
    }
}
