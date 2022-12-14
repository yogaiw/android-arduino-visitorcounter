package com.hureyo.viscount

import android.content.Intent
import android.media.audiofx.Visualizer
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.renderscript.Sampler
import androidx.appcompat.app.AppCompatDelegate
import com.google.android.material.bottomsheet.BottomSheetDialog
import com.google.firebase.database.*

import com.google.firebase.ktx.Firebase
import com.hureyo.viscount.model.Visitor
import kotlinx.android.synthetic.main.activity_main.*
import android.view.animation.Animation

import android.view.animation.AlphaAnimation
import android.widget.Button

class MainActivity : AppCompatActivity() {

    private val myRef = FirebaseDatabase.getInstance().getReference().child("Data")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO)

        myRef.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(p0: DataSnapshot) {
                val visitor = p0.getValue(Visitor::class.java)
                tv_masuk.text = visitor?.masuk.toString()
                tv_keluar.text = visitor?.keluar.toString()
                tv_total.text = visitor?.total.toString()
            }
            override fun onCancelled(p0: DatabaseError) {
                TODO("Not yet implemented")
            }
        })

        val anim: Animation = AlphaAnimation(0.5f, 1.0f)
        anim.duration = 50
        anim.startOffset = 20
        anim.repeatMode = Animation.REVERSE
        anim.repeatCount = 2

        myRef.child("masuk").addValueEventListener(object : ValueEventListener {
            override fun onDataChange(p0: DataSnapshot) {
                layout_masuk.startAnimation(anim)
            }

            override fun onCancelled(p0: DatabaseError) {
                TODO("Not yet implemented")
            }
        })

        myRef.child("keluar").addValueEventListener(object : ValueEventListener {
            override fun onDataChange(p0: DataSnapshot) {
                layout_keluar.startAnimation(anim)
            }

            override fun onCancelled(p0: DatabaseError) {
                TODO("Not yet implemented")
            }
        })
        myRef.child("total").addValueEventListener(object : ValueEventListener {
            override fun onDataChange(p0: DataSnapshot) {
                layout_total.startAnimation(anim)
            }

            override fun onCancelled(p0: DatabaseError) {
                TODO("Not yet implemented")
            }
        })

        val infoBottomSheet = BottomSheetDialog(this)
        val resetConfirmation = BottomSheetDialog(this)
        infoBottomSheet.setContentView(R.layout.bottom_sheet_info)
        resetConfirmation.setContentView(R.layout.bottom_sheet_reset_confirmation)

        btn_info.setOnClickListener {
            infoBottomSheet.show()
        }

        btn_keSuhu.setOnClickListener {
//            resetConfirmation.show()
            val intent = Intent(this, SuhuActivity::class.java)
            startActivity(intent)
        }

        resetConfirmation.findViewById<Button>(R.id.btn_confirm_ya)?.setOnClickListener {
            resetVisitor(0,0,0)
            resetConfirmation.hide()
        }
        resetConfirmation.findViewById<Button>(R.id.btn_confirm_tidak)?.setOnClickListener {
            resetConfirmation.hide()
        }
    }

    private fun resetVisitor(masuk: Int, keluar: Int, total: Int) {
        val visitor = Visitor(masuk, keluar, total)
        myRef.setValue(visitor)
    }
}